// force_kernel.cuh
#ifndef FORCE_KERNEL_CUH
#define FORCE_KERNEL_CUH

__device__ double periodic(double x, double box_length);

__global__ void computeForcesKernel(
    const double *x, const double *y,
    double *fx, double *fy,
    int N, double BOX_X, double BOX_Y,
    double CUTOFF_2);

// 封装的计算力的函数
void computeForces(
    const double *x, const double *y,
    double *fx, double *fy,
    int N, double BOX_X, double BOX_Y, double CUTOFF_2);

#endif // FORCE_KERNEL_CUH
