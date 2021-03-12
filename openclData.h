//
// Created by harish on 10.03.21.
//

#ifndef UNIFIEDINTERFACE_OPENCLDATA_H
#define UNIFIEDINTERFACE_OPENCLDATA_H

#include <CL/cl.h>

class openclData {

public:
    cl_platform_id* getPlatforms();

    cl_uint getNumDevices(cl_platform_id* platforms);

    cl_device_id* getDevices(cl_uint numDevices,cl_platform_id* platforms);

    cl_context getContext(cl_device_id devices, cl_uint numDevices);

    cl_command_queue getCmdQueue(cl_context context, cl_device_id* devices);

    cl_mem hostToDevice(cl_context context,int dataSize,cl_command_queue cmdQueue,int* hostData);

    cl_mem getOpenclData(int dataSize, int* hostData);

    int *getOpenclHostData(int dataSize, cl_mem devData);

    int *deviceToHost(int dataSize, cl_mem devData,cl_command_queue cmdQueue);

    cl_mem createBuffer(cl_context context, int dataSize, int *cudaData);
};


#endif //UNIFIEDINTERFACE_OPENCLDATA_H
