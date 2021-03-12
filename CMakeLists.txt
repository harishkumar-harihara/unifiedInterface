cmake_minimum_required(VERSION 3.15)
SET(CMAKE_CUDA_COMPILER /usr/local/cuda-11.2/bin/nvcc)
project(unifiedInterface LANGUAGES CUDA CXX)

set(CMAKE_CUDA_STANDARD 14)

find_package(OpenCL REQUIRED)
FIND_PACKAGE(ArrayFire REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ArrayFire_INCLUDE_DIRS})

add_library(unified STATIC
        HostData.h HostData.cpp
        openclData.cpp openclData.h cudaData.cu cudaData.cuh test.cpp test.h thrustData.cu thrustData.cuh arrayfireData.cu arrayfireData.cuh boostData.cpp boostData.h)

target_compile_features(unified PUBLIC cxx_std_14)

set_target_properties(unified
        PROPERTIES
        CUDA_SEPRARABLE_COMPILATION ON)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} \
    --expt-extended-lambda \
    ")

add_executable(unifiedInterface
        main.cu)

set_property(TARGET unifiedInterface PROPERTY CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(unifiedInterface PRIVATE unified)

TARGET_LINK_LIBRARIES(unifiedInterface LINK_PUBLIC ${OpenCL_LIBRARIES} ${ArrayFire_LIBRARIES})

set_target_properties(
        unifiedInterface
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

