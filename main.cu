#include <iostream>
#include "test.h"
#include "thrustData.cuh"
#include "arrayfireData.cuh"
#include "boostData.h"

using namespace std;

int main() {
//    auto obj = new test();
//    obj->interaction();
//    auto obj = new thrustData();
//    obj->cudaToThrust();
//    auto obj = new arrayfireData();
//    obj->cudaToAF();
    auto obj = new boostData();
    obj->cudaToBoost();
}
