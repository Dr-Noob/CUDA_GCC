#include <stdio.h>
#include <stdlib.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include "helper_cuda.h"
#include "kernel.h"

int main() {
  cudaError_t err = cudaSuccess;
  int size = 1000;

  float *h_result;
  float *d_result;

  float *h_data;
  float *d_data;

  if((h_data = (float *)malloc(size)) == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  if((h_result = (float *)malloc(size)) == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  if ((err = cudaMalloc((void **)&d_data, size)) != cudaSuccess) {
    cudaGetErrorName(err);
    return EXIT_FAILURE;
  }

  if ((err = cudaMalloc((void **)&d_result, size)) != cudaSuccess) {
    cudaGetErrorName(err);
    return EXIT_FAILURE;
  }

  if ((err = cudaMemcpy(d_data, h_data, size, cudaMemcpyHostToDevice)) != cudaSuccess) {
    cudaGetErrorName(err);
    return EXIT_FAILURE;
  }

  int threadsPerBlock = 256;
  int blocksPerGrid = (size + threadsPerBlock - 1) / threadsPerBlock;

  my_wrap(threadsPerBlock, blocksPerGrid, d_data, d_result, size);

  if ((err = cudaGetLastError()) != cudaSuccess) {
    cudaGetErrorName(err);
    return EXIT_FAILURE;
  }

  if ((err = cudaMemcpy(h_result, d_result, size, cudaMemcpyDeviceToHost)) != cudaSuccess) {
    cudaGetErrorName(err);
    return EXIT_FAILURE;
  }

  cudaDeviceReset();
}
