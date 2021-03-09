#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix M3 = MakeOnes(6,6);
    const SparseMatrix M1 = M3;
    SparseMatrix M5(3,3);
    const SparseMatrix M6 = M5;
    M1[0][0];
    M1[0][1];
    std::cout <<*(*(M1 + 2) + 1)<<std::endl;
    SparseMatrix M2(4,4);
    try{
        M3 = M2;
    }
    catch(...){}
    try{
        M3 + M2;
    }
    catch(...){}
    try{
        M3 = M3;
    }
    catch(...){

    }
    **M1;
    return 0;
}
