//
// Created by harish on 10.03.21.
//

#include "cudaData.cuh"
#include <iostream>
using namespace std;

int* cudaData::getData(int dataSize,int* hostData) {
    int* deviceVec;
    cudaMallocManaged(&deviceVec,dataSize*sizeof(int));
    cudaMemcpy(deviceVec, hostData, dataSize*sizeof (int),cudaMemcpyHostToDevice);
    return deviceVec;
}

int* cudaData::copyHostToDevice(int* deviceVec, int* hostData, int dataSize){
    cudaMemcpy(deviceVec, hostData, dataSize*sizeof (int),cudaMemcpyHostToDevice);
    return deviceVec;
}

int* cudaData::allocateGpuMemory(int dataSize, int* hostData){
    int* deviceVec;
    cudaMalloc(&deviceVec,dataSize*sizeof(int));
    return deviceVec;
}

int* cudaData::getHostData(int dataSize,int* devData) {
    int* hostData = (int*)malloc(sizeof (int)*dataSize);
    cudaMemcpy(hostData,devData, sizeof(int)*dataSize,cudaMemcpyDeviceToHost);
    return hostData;
}