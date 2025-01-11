// force_kernel.cu
#include "force_kernel.cuh"
#include <cuda_runtime.h>
#include <stdexcept>

#define CUDA_CHECK(call)                                       \
    do                                                         \
    {                                                          \
        cudaError_t err = call;                                \
        if (err != cudaSuccess)                                \
        {                                                      \
            throw std::runtime_error(cudaGetErrorString(err)); \
        }                                                      \
    } while (0)

__device__ double periodic(double x, double box_length)
{
    return x - floor(x / box_length) * box_length;
}

__global__ void computeForcesKernel(
    const double *x, const double *y,
    double *fx, double *fy,
    int N, double BOX_X, double BOX_Y,
    double CUTOFF_2)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N)
        return;

    double xi = x[i];
    double yi = y[i];

    // 避免使用局部变量进行原子操作
    for (int j = 0; j < N; ++j)
    {
        if (i >= j)
            continue; // 避免重复计算

        double dx = xi - x[j];
        double dy = yi - y[j];

        // 应用周期性边界条件
        dx = periodic(dx, BOX_X);
        dy = periodic(dy, BOX_Y);

        double r2 = dx * dx + dy * dy;
        if (r2 < CUTOFF_2)
        {
            double r2i = 1.0 / r2;
            double r6i = r2i * r2i * r2i;
            double lj = 48.0 * r2i * r6i * (r6i - 0.5);
            double fx_ij = lj * dx;
            double fy_ij = lj * dy;

            // 使用原子操作更新全局内存中的力
            atomicAdd(&fx[i], fx_ij);
            atomicAdd(&fy[i], fy_ij);
            atomicAdd(&fx[j], -fx_ij);
            atomicAdd(&fy[j], -fy_ij);
        }
    }
}

// 封装计算力的函数
void computeForces(
    const double *x, const double *y,
    double *fx, double *fy,
    int N, double BOX_X, double BOX_Y, double CUTOFF_2)
{
    // 定义CUDA网格和块的尺寸
    dim3 threadsPerBlock(256);                                           // 每个线程块256个线程
    dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x); // 计算网格大小

    // 启动CUDA核函数
    computeForcesKernel<<<blocksPerGrid, threadsPerBlock>>>(x, y, fx, fy, N, BOX_X, BOX_Y, CUTOFF_2);

    // 检查内核启动是否有错误
    CUDA_CHECK(cudaGetLastError());
}
