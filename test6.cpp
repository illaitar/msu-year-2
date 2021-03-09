#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    const SparseMatrix M1 = MakeOnes(5,5);
    *(*(M1 + 1 + 1) + 1 + 1);
    *(1 + *(1 + M1 + 1 ) + 1 + 1);
    SparseMatrix M2(3,3);
    *(*(M2 + 1) + 1 + 1) = 2;
    *(1 + *(1 + 1 + M2) + 1) = 2;
    return 0;
}
