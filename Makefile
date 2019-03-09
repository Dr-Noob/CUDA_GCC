CUDA_PATH            ?= /opt/cuda
CUDA_INC_PATH        ?= $(CUDA_PATH)/include
CUDA_INC_PATH_COMMON ?= /opt/cuda/samples/common/inc/

CUDA_BIN_PATH        ?= $(CUDA_PATH)/bin
CUDA_LIB_PATH        ?= $(CUDA_PATH)/lib64

all: test   

test: kernel.o main.cpp Makefile
	g++ -I$(CUDA_INC_PATH) -I$(CUDA_INC_PATH_COMMON) -L$(CUDA_LIB_PATH) -lcuda -lcudart main.cpp kernel.o -o test

kernel.o: kernel.cu Makefile
	nvcc -c kernel.cu

clean: 
	rm -rf *o test
