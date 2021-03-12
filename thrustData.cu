//
// Created by harish on 11.03.21.
//

#include "thrustData.cuh"
#include "cudaData.cuh"
#include "HostData.h"
#include <thrust/device_vector.h>
#include <iostream>
using namespace std;

void thrustData::cudaToThrust() {
    int dataSize = 1024;

    auto host = new HostData();
    int* hostData = host->createData(dataSize);

    // Transfer data from host to CUDA buffers and back
    auto *cudaObj = new cudaData();
    int*  cudaPtr = cudaObj->getData(dataSize,hostData);

    thrust::device_ptr<int> thrustPtr(cudaPtr);
    thrust::device_vector<int> thrustVec(thrustPtr,thrustPtr+dataSize);
    thrust::host_vector<int> hostVec = thrustVec;

    int result = 1;
    for(int i = 0; i < dataSize; i++){
        if(hostVec[i] != hostData[i]){
            result = 0;
            break;
        }
    }

    if(result){
        cout << "working" << endl;
    }else{
        cout << "try again";
    }

}