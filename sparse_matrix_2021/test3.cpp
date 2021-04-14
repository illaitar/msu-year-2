#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix M1 = MakeOnes(3,3);
    M1.get(0,0);
    M1.get(0,1);
    M1.set(0,1,1);
    SparseMatrix M2 = MakeOnes(3,3);
    SparseMatrix M3 = M1 + M2;
    try{
        M3.get(16,1);
    }
    catch(...){

    }
    return 0;
}
