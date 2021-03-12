//
// Created by harish on 10.03.21.
//

#include <iostream>
#include <cmath>
#include "test.h"
#include "HostData.h"
#include "openclData.h"
#include "cudaData.cuh"

using namespace std;

void test::conversion() {
    int dataSize = pow(2,10);

    // Create Host Data
    auto host = new HostData();
    int* hostData = host->createData(dataSize);

    // Transfer data from host to CUDA buffers and back
    cudaData *cudaObj = new cudaData();
    int* cudaData = cudaObj->getData(dataSize,hostData);
    int* cudaHostData = cudaObj->getHostData(dataSize,cudaData);

    // Transfer data from host to OpenCL buffers and back
    auto openclObj = new openclData();
    cl_platform_id* platforms = openclObj->getPlatforms();
    cl_uint numDevices = openclObj->getNumDevices(&platforms[0]);
    cl_device_id* devices = openclObj->getDevices(numDevices,&platforms[0]);
    cl_context context = openclObj->getContext(devices[0],numDevices);
    cl_command_queue cmdQueue = openclObj->getCmdQueue(context,&devices[0]);
    cl_mem bufData = openclObj->hostToDevice(context,dataSize,cmdQueue,hostData); // proper from host to opencl conversion
//    cl_mem bufData = openclObj->hostToDevice(context,dataSize,cmdQueue,cudaData); // trying out cuda pointer to clEnqueueWriteBuffer
    int* openclHostData = openclObj->deviceToHost(dataSize,bufData,cmdQueue);    // proper from opencl to host conversion


    // Test if both the copy are successful or not
    int result = 1;
    for(int i = 0; i < dataSize; i++){
        if(cudaHostData[i] != openclHostData[i]){
            result = 0;
            break;
        }
    }

    if(result){
        cout << "Operation successful" << endl;
    }else{
        cout << "Operation failed" << endl;
    }
}

void test::interaction() {

    int dataSize = pow(2,10);

    // Create Host Data
    auto host = new HostData();
    int* hostData = host->createData(dataSize);


    // Transfer data from host to CUDA buffers and back
    cudaData *cudaObj = new cudaData();
    int* cudaData = cudaObj->allocateGpuMemory(dataSize,hostData);

    // Transfer data from host to OpenCL buffers and back
    auto openclObj = new openclData();
    cl_platform_id* platforms = openclObj->getPlatforms();
    cl_uint numDevices = openclObj->getNumDevices(&platforms[0]);
    cl_device_id* devices = openclObj->getDevices(numDevices,&platforms[0]);
    cl_context context = openclObj->getContext(devices[0],numDevices);
    cl_command_queue cmdQueue = openclObj->getCmdQueue(context,&devices[0]);
    cl_mem buffer = openclObj->createBuffer(context,dataSize,cudaData);

    // data is copied from host to device memory using cudaMemCpy
    cudaData = cudaObj->copyHostToDevice(cudaData,hostData,dataSize);

    // data is read from device to host using clEnqueueReadBuffer
    int* returnedHostData = openclObj->deviceToHost(dataSize,buffer,cmdQueue);

    // Test if both the copy are successful or not
    int result = 1;
    for(int i = 0; i < dataSize; i++){
        if(hostData[i] != returnedHostData[i]){
            result = 0;
            break;
        }
    }

    if(result){
        cout << "Operation successful" << endl;
    }else{
        cout << "Operation failed" << endl;
    }
}