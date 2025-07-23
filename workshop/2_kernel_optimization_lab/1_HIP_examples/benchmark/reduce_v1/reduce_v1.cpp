#include <hip/hip_runtime.h>
#include <random>
#include <iostream>

#include "reduce_sum.hpp"


int main() {
    const uint32_t WARP_SIZE = 64;
    const uint32_t THREAD_PER_BLOCK = 256;
    const int N = 128 * 1024 * 1024;
    const int block_num = N / THREAD_PER_BLOCK;
    
    int *h_in, *h_out;
    int *d_in, *d_out;
    h_in = (int*)malloc(N * sizeof(int));
    h_out = (int*)malloc(block_num * sizeof(int));
    hipMalloc(&d_in, N * sizeof(int));
    hipMalloc(&d_out, block_num * sizeof(int));
    double sum = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 10);
    for(size_t i = 0; i < N; i++){
        h_in[i] = dis(gen);
        sum += h_in[i];
    }
    hipMemcpy(d_in, h_in, N * sizeof(int), hipMemcpyHostToDevice);

    int num_warmup = 20, num_repeat = 100;
    float total_time = 0.0f, milliseconds = 0.0f;
    hipEvent_t start, stop;
    hipEventCreate(&start);
    hipEventCreate(&stop);
    
    dim3 grid(block_num, 1);
    dim3 block(THREAD_PER_BLOCK, 1);
    const size_t smem_size = THREAD_PER_BLOCK * sizeof(int);
    // warmup
    for (int i = 0; i < num_warmup; i++) {
        reduce_kernel_v1<<<grid, block, smem_size>>>(d_in, d_out, N);
    }
    // repeat
    for (size_t i = 0; i < num_repeat; i++)
    {
        hipEventRecord(start);
        reduce_kernel_v1<<<grid, block, smem_size>>>(d_in, d_out, N);
        hipEventRecord(stop);
        hipEventSynchronize(stop);
        hipEventElapsedTime(&milliseconds, start, stop);
        total_time += milliseconds;
    }
    hipEventDestroy(start);
    hipEventDestroy(stop);
    float seconds = total_time / num_repeat / 1000.0;
    hipError_t err = hipGetLastError();
    if (err != hipSuccess) {
        std::cerr << "Error: " << hipGetErrorString(err) << std::endl;
        free(h_in);
        free(h_out);
        hipFree(d_in);
        hipFree(d_out);
        return -1;
    }
    
    hipMemcpy(h_out, d_out, block_num * sizeof(int), hipMemcpyDeviceToHost);
    double sum_out = 0;
    for(int i = 0; i < block_num; i++)
    {
        sum_out += h_out[i];
    }

    // compute bandwidth
    int total_bytes = N * sizeof(int);
    float bw = (float)total_bytes / seconds / 1e9;
    
    if (fabs(sum - sum_out) > 1e-2)
    {
        std::cerr << "reduce_kernel_v1 check failed: sum=" << sum 
             << ", sum_out=" << sum_out 
             << ", diff=" << fabs(sum - sum_out) << std::endl;
    }
    std::cout << "reduce_kernel_v1: latency=" << seconds*1000.0 
              << " ms, bandwidth=" << bw << " GB/s" << std::endl;
    
    free(h_in);
    free(h_out);
    hipFree(d_in);
    hipFree(d_out);
    return 0;
}