//
// Created by harish on 10.03.21.
//

#ifndef UNIFIEDINTERFACE_CUDADATA_CUH
#define UNIFIEDINTERFACE_CUDADATA_CUH


class cudaData {
public:
    int* getData(int dataSize,int* hostData);
    int *getHostData(int dataSize, int* devData);

    int *allocateGpuMemory(int dataSize, int *hostData);

    int *copyHostToDevice(int* deviceVec, int* hostData, int dataSize);
};


#endif //UNIFIEDINTERFACE_CUDADATA_CUH
