#ifndef __REDUCE_SUM_HPP__
#define __REDUCE_SUM_HPP__
#include <hip/hip_runtime.h>
#include <stdio.h>



template<typename T>
__global__ void reduce_kernel_v0(T* input, T* output, int n) {
    extern __shared__ T shared[];
    const uint32_t tid = threadIdx.x;
    const uint32_t i = blockIdx.x * blockDim.x + threadIdx.x;
    shared[tid] = input[i];
    __syncthreads();
    for (uint32_t i = 1; i < blockDim.x; i *= 2) {
        if (tid % (2 * i) == 0) {
            shared[tid] += shared[tid + i];
        }
        __syncthreads();
    }

    if (tid == 0) {
        output[blockIdx.x] = shared[0];
    }
}

template<typename T>
__global__ void reduce_kernel_v1(T* input, T* output, int n) {
    extern __shared__ T shared[]; 
    const uint32_t tid = threadIdx.x;
    const uint32_t i = blockIdx.x * blockDim.x + threadIdx.x;
    shared[tid] = input[i];
    __syncthreads();
    for (uint32_t i = 1; i < blockDim.x; i *= 2) {
        uint32_t index = 2 * i * threadIdx.x;
        if (index < blockDim.x) {
            shared[index] += shared[index + i];
        }
        __syncthreads();
    }

    if (tid == 0) {
        output[blockIdx.x] = shared[0];
    }
}

template<typename T>
__global__ void reduce_kernel_v2(T* input, T* output, int n) {
    extern __shared__ T shared[]; 
    const uint32_t tid = threadIdx.x;
    const uint32_t i = blockIdx.x * blockDim.x + threadIdx.x;
    shared[tid] = input[i];
    __syncthreads();
    for (uint32_t i= blockDim.x / 2; i > 0; i /= 2) {
        if (threadIdx.x < i) {
            shared[threadIdx.x] += shared[threadIdx.x + i];
        }
        __syncthreads();
    }

    if (tid == 0) {
        output[blockIdx.x] = shared[0];
    }
}

template<typename T>
__global__ void reduce_kernel_v3(T *input, T* output, int n) {
    extern __shared__ T shared[];
    T *input_begin = input + blockDim.x * blockIdx.x * 2;
    const uint32_t tid = threadIdx.x;
    shared[tid] = input_begin[tid] + input_begin[tid + blockDim.x];
    __syncthreads();
    for (uint32_t i = blockDim.x / 2; i > 0; i /= 2) {
        if (threadIdx.x < i) {
            shared[threadIdx.x] += shared[threadIdx.x + i];
        }
        __syncthreads();
    }

    if (tid == 0) {
        output[blockIdx.x] = shared[0];
    }
}

template<uint32_t BLOCK_SIZE, typename T>
__global__ void reduce_kernel_v4(T *input, T* output, int n) {
    volatile __shared__ T shared[BLOCK_SIZE];
    T *input_begin = input + blockDim.x * blockIdx.x * 2;
    const uint32_t tid = threadIdx.x;
    shared[tid] = input_begin[tid] + input_begin[tid + blockDim.x];
    __syncthreads();

    for (uint32_t i = blockDim.x / 2; i > 64; i /= 2) {
        if (threadIdx.x < i) {
            shared[threadIdx.x] += shared[threadIdx.x + i];
        }
        __syncthreads(); 
    }

    if (tid < 64) {
        shared[tid] += shared[tid + 64];
        shared[tid] += shared[tid + 32];
        shared[tid] += shared[tid + 16];
        shared[tid] += shared[tid + 8];
        shared[tid] += shared[tid + 4]; 
        shared[tid] += shared[tid + 2];
        shared[tid] += shared[tid + 1];
    }

    if (tid == 0) {
        output[blockIdx.x] = shared[0];
    }
}

template<uint32_t BLOCK_SIZE, typename T>
__global__ void reduce_kernel_v5(T *input, T* output, int n) {
    volatile __shared__ T shared[BLOCK_SIZE];
    T *input_begin = input + blockDim.x * blockIdx.x * 2;
    const uint32_t tid = threadIdx.x;
    shared[tid] = input_begin[tid] + input_begin[tid + blockDim.x];
    __syncthreads();
    
    if (tid < 128) { 
        shared[tid] += shared[tid + 128];
        __syncthreads();
    }

    if (tid < 64) {
        shared[tid] += shared[tid + 64];
        shared[tid] += shared[tid + 32];
        shared[tid] += shared[tid + 16];
        shared[tid] += shared[tid + 8];
        shared[tid] += shared[tid + 4]; 
        shared[tid] += shared[tid + 2];
        shared[tid] += shared[tid + 1];
    }

    if (tid == 0) {
        output[blockIdx.x] = shared[0];
    }
}


#endif // __REDUCE_SUM_HPP__
