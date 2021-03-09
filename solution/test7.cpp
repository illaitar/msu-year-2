#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix M1(3,3), M2(3,3),M4(3,3),M5(5,5),M6(3,3),M7(10,10);
    M1 = MakeOnes(3,3);
    M5 = MakeOnes(5,5);
    bool q;
    q = M1 == M2;
    q = M1 != M2;
    q = M4 == M2;
    q = M1 == M5;
    M6 = MakeOnes(3,3);
    M6.set(0,1,2);
    q = M1 == M6;
    q = M1 == M1;

    *(1 + *(1 + 1 + (M7 + 1) + 1) + 1);
    return 0;
}
