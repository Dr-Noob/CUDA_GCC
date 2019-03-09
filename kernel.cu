#include <cuda_runtime.h>

__global__
void vectorAdd(float *idata, float *odata, int size) {
  /* really interesting computation */  
}

void my_wrap(int blocksPerGrid, int threadsPerBlock, float *idata, float *odata, int size) {
  vectorAdd<<<blocksPerGrid, threadsPerBlock, 0>>>(idata, odata, size);
}
