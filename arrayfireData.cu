//
// Created by harish on 11.03.21.
//

#include "arrayfireData.cuh"
#include "cudaData.cuh"
#include "HostData.h"
#include <af/array.h>
#include <arrayfire.h>
#include <iostream>
#include <vector>

using namespace std;

void arrayfireData::cudaToAF() {
    int dataSize = 1024;

    auto host = new HostData();
    int* hostData = host->createData(dataSize);

    // Transfer data from host to CUDA buffers and back
    auto *cudaObj = new cudaData();
    int*  cudaPtr = cudaObj->getData(dataSize,hostData);

    af::array deviceData((dim_t)dataSize, cudaPtr, afDevice);
    std::vector<int> returnedHostData(deviceData.elements());
    deviceData.host(returnedHostData.data());

    int result = 1;
    for(int i = 0; i < dataSize; i++){
        if(returnedHostData[i] != hostData[i]){
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