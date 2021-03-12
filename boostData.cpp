//
// Created by harish on 11.03.21.
//

#include "boostData.h"
#include "HostData.h"
#include "cudaData.cuh"
#include "openclData.h"
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/device_ptr.hpp>
#include <boost/compute/algorithm/for_each_n.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>
#include <vector>
#include <iostream>

using namespace std;
namespace compute = boost::compute;

void boostData::cudaToBoost() {

    int dataSize = 1024;

    auto host = new HostData();
    int* hostData = host->createData(dataSize);

    // Transfer data from host to CUDA buffers and back
    auto *cudaObj = new cudaData();
    int* cudaPtr = cudaObj->getData(dataSize,hostData);

    // Boost Compute instance
    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);

    cl_int status;
    cl_mem clMemSrc = clCreateBuffer(context,CL_MEM_ALLOC_HOST_PTR,dataSize*sizeof (int),NULL,&status);
    status = clEnqueueWriteBuffer(queue,clMemSrc,CL_FALSE,0,dataSize*sizeof (int),cudaPtr,
                                  0,NULL,NULL);
    int* returnedHostData = (int*)malloc(dataSize* sizeof(int));
    status = clEnqueueReadBuffer(queue,clMemSrc,CL_TRUE,0,dataSize* sizeof(int),
                                 returnedHostData,0,NULL,NULL);

    compute::vector<int> vec1(dataSize,context);
    compute::copy(cudaPtr,cudaPtr+dataSize,vec1.begin(),queue);

    vector<int> hostFromBoost(vec1.size());
    compute::copy(vec1.begin(),vec1.end(),hostFromBoost.begin(),queue);


    int result = 1;
    for(int i = 0; i < dataSize; i++){
        if(hostFromBoost[i] != hostData[i]){
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