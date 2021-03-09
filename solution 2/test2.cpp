#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix M1(3,3), M2(3,3);
    M1[0][0] = 1;
    M1[1][1] = 1;
    M1[2][2] = 1;
    *(*(M2)) = 1;
    M2[0][1] = 2;
    M2[0][2] = 3;
    *((*(M2 + 2)) + 0) = 4;
    M2[1][1] = 5;
    M2[1][2] = 6;
    M2[2][0] = 7;
    M2[2][1] = 8;
    M2[2][2] = 9;
    M1 * M2;
    M1.set(0,0,1);
    return 0;
}
