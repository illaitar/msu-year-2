#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix M1(3,3);
    SparseMatrix M2(3,3);
    M1 = M2;
    M1[2][2] = M2[2][2];
    M1[1][1] = 1;
    SparseMatrix M3 = MakeOnes(3,3);
    try{
        M1[4][2] = 3;
    }
    catch(...){

    }
    SparseMatrix M4(5,6);
    try{
        M4 = M1;
    }
    catch(...){

    }
    try{
        M4.set(16,0,19);
    }
    catch(...){

    }
    return 0;
}
