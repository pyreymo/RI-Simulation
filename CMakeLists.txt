cmake_minimum_required(VERSION 3.20)
project(MolecularDynamics_GPU)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)

# 查找 CUDA 工具包
find_package(CUDAToolkit REQUIRED)

# 查找 Eigen3 库
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# 包含头文件目录
include_directories(include)
include_directories(cuda)

# 设置 CUDA 架构
set(CMAKE_CUDA_ARCHITECTURES 86)
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)

# 启用 CUDA 语言
enable_language(CUDA)

# 添加源文件并指定目标可执行文件
add_executable(MolecularDynamics_GPU
    src/simulation.cpp
    src/MolecularDynamics.cpp
    src/Particle.cpp
    src/Box.cpp
    src/Force.cpp
    src/Logline.cpp
    src/Sample.cpp
    cuda/force_kernel.cu
)

# 链接 Eigen3 和 CUDA 库
target_link_libraries(MolecularDynamics_GPU PRIVATE Eigen3::Eigen CUDA::cudart)

# 启用 CUDA 分离编译
set_target_properties(MolecularDynamics_GPU PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

# 设置编译选项
target_compile_options(MolecularDynamics_GPU PRIVATE
    -O2
)
