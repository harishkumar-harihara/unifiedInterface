//
// Created by harish on 10.03.21.
//

#include "HostData.h"

int* HostData::createData(int elements){
    int *A = NULL;
    size_t datasize = sizeof(int)*elements;
    A = (int*)malloc(datasize);
    for(int i=0; i < elements; i++){
        A[i] = i;
    }
    return A;
}