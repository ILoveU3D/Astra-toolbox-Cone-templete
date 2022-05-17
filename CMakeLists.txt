# 声明最低版本，项目名称，引入CUDA包，加入ASTRA_CUDA宏定义
# 需要提前安装：CUDA和boost库
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(astra)
find_package(CUDA)
add_definitions(-DASTRA_CUDA)

# 引入头文件
include_directories(include)
include_directories(astra-2.1.0/astra)
include_directories(astra-2.1.0/astra/cuda/2d)
include_directories(astra-2.1.0/astra/cuda/3d)

# 引入.cu文件和.cpp文件，cpp文件放在一起编译，cu文件做成静态链接库
file(GLOB ASTRA_SRC_CUDA2D "astra-2.1.0/cuda/2d/*.cu")
file(GLOB ASTRA_SRC_CUDA3D "astra-2.1.0/cuda/3d/*.cu")
cuda_add_library(2D ${ASTRA_SRC_CUDA2D})
cuda_add_library(3D ${ASTRA_SRC_CUDA3D})
aux_source_directory(. MAIN)
aux_source_directory(src TOOL)
aux_source_directory(astra-2.1.0 ASTRA_SRC)
add_executable(main ${TOOL} ${ASTRA_SRC} ${MAIN})
target_link_libraries(main 2D 3D cufft)

# 指定编译器为nvcc，不带附加编译项
# 注意CUDA版本
set(CMAKE_CXX_COMPILER /usr/local/cuda/bin/nvcc)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")