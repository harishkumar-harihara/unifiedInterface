//
// Created by harish on 10.03.21.
//

#include <iostream>
#include "openclData.h"
using namespace std;

cl_platform_id* openclData::getPlatforms(){
    cl_int status;
    cl_uint numPlatforms = 0;
    status = clGetPlatformIDs(0,NULL,&numPlatforms);
//    cout << status << endl;

    cl_platform_id *platforms = NULL;
    platforms = (cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));

    status = clGetPlatformIDs(numPlatforms,platforms,NULL);
//    cout << status << endl;
    return platforms;
}

cl_uint openclData::getNumDevices(cl_platform_id* platforms){
    cl_int status;
    cl_uint numDevices = 0;
    status = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,0,NULL,&numDevices);
//    cout << status << endl;
    return numDevices;
}

cl_device_id* openclData::getDevices(cl_uint numDevices,cl_platform_id* platforms){
    cl_int status;
    cl_device_id *  devices;
    devices = (cl_device_id*)malloc(numDevices*sizeof(cl_device_id));

    status = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,numDevices,devices,NULL);
//    cout << status << endl;
    return devices;
}

cl_context openclData::getContext(cl_device_id devices, cl_uint numDevices){
    cl_int status;
    cl_context context;
    context = clCreateContext(NULL,numDevices,&devices,NULL,NULL,&status);
//    cout << status << endl;
    return context;
}

cl_command_queue openclData::getCmdQueue(cl_context context, cl_device_id* devices){
    cl_int status;
    cl_command_queue cmdQueue;
    cmdQueue = clCreateCommandQueue(context,devices[0],0,&status);
//    cout << status << endl;
    return cmdQueue;
}

cl_mem openclData::hostToDevice(cl_context context,int dataSize,cl_command_queue cmdQueue,int* hostData){
    cl_int status;
    cl_mem bufA = clCreateBuffer(context,CL_MEM_READ_ONLY,dataSize*sizeof(int),NULL,NULL);
    status = clEnqueueWriteBuffer(cmdQueue,bufA,CL_FALSE,0,dataSize*sizeof (int),hostData,0,NULL,NULL);
    cout << status << endl;
    return bufA;
}

cl_mem openclData::createBuffer(cl_context context,int dataSize,int* cudaData){
    cl_int status;
    cl_mem bufA = clCreateBuffer(context,CL_MEM_READ_ONLY,dataSize*sizeof(int),cudaData,&status);
    return bufA;
}

int* openclData::deviceToHost(int dataSize, cl_mem devData,cl_command_queue cmdQueue){
    cl_int status;
    int* hostData = (int*)malloc(dataSize*sizeof (int));
    status = clEnqueueReadBuffer(cmdQueue,devData,CL_TRUE,0,dataSize*sizeof(int),hostData,0,NULL,NULL);
//    cout << status << endl;
    return hostData;
}

cl_mem openclData::getOpenclData(int dataSize, int* hostData){
    auto openclObj = new openclData();
    cl_platform_id* platforms = openclObj->getPlatforms();
    cl_uint numDevices = openclObj->getNumDevices(&platforms[0]);
    cl_device_id* devices = openclObj->getDevices(numDevices,&platforms[0]);
    cl_context context = openclObj->getContext(devices[0],numDevices);
    cl_command_queue cmdQueue = openclObj->getCmdQueue(context,&devices[0]);
    cl_mem bufData = openclObj->hostToDevice(context,dataSize,cmdQueue,hostData);
//    int* openclHostData = openclObj->deviceToHost(dataSize,bufData,cmdQueue);
    return bufData;
}

int* openclData::getOpenclHostData(int dataSize, cl_mem devData){
    cl_int status;
    cl_uint numPlatforms = 0;
    status = clGetPlatformIDs(0,NULL,&numPlatforms);
    cout << status << endl;

    cl_platform_id *platforms = NULL;
    platforms = (cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));

    status = clGetPlatformIDs(numPlatforms,platforms,NULL);
    cout << status << endl;

    cl_uint numDevices = 0;
    status = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,0,NULL,&numDevices);
    cout << status << endl;

    cl_device_id *   devices;
    devices = (cl_device_id*)malloc(numDevices*sizeof(cl_device_id));
    status = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,numDevices,devices,NULL);
    cout << status << endl;

    cl_context context;
    context = clCreateContext(NULL,numDevices,devices,NULL,NULL,&status);
    cout << status << endl;

    cl_command_queue cmdQueue;
    cmdQueue = clCreateCommandQueue(context,devices[0],0,&status);
    cout << status << endl;

    int* hostData = (int*)malloc(dataSize*sizeof (int));
    status = clEnqueueReadBuffer(cmdQueue,devData,CL_TRUE,0,dataSize*sizeof(int),hostData,0,NULL,NULL);
    cout << status << endl;
    return hostData;
}