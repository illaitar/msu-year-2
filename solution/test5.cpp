#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix M3 = MakeOnes(6,6);
    *(M3[0] + 1) = 3;
    const SparseMatrix M4 = MakeOnes(6,6);
    *(M4[1] + 1);
    *(*(M4));
    const SparseMatrix M5(4,4);
    *(*(M5));
    return 0;
}
