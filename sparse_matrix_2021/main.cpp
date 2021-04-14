#include "SparseMatrix.hpp"
#include <iostream>

int main () {
    SparseMatrix Matr(10,10);
    Matr.set(3,6, 3.14);
    Matr.set(2,6, 5.18);
    SparseMatrix Matr2(10,10);
    Matr2.set(3,6, 6.86);
    Matr2.set(1,6, 3);
    Matr2.set(1,5, 1000);
    SparseMatrix Matr3(10,10);
    Matr3 = Matr + Matr2;
    std::cout << Matr3.get(3,6) << std::endl;
    std::cout << Matr3.get(1,6) << std::endl;
    std::cout << Matr3.get(2,6) << std::endl;
    std::cout << Matr3.get(1,5) << std::endl;
    std::cout << Matr3[1][5] <<std::endl;
    Matr3[1][5] += 6;
    std::cout << Matr3[1][5] <<std::endl;
    Matr3[7][7] = 18;
    std::cout << Matr3[7][7] <<std::endl;
    SparseMatrix Matr4(2,2);
    Matr4[0][0] = 2;
    Matr4[0][1] = 3;
    Matr4[1][0] = 3;
    Matr4[1][1] = 3;
    **Matr4;
    const SparseMatrix matrix5(10,10);
    **matrix5;
    *(*(1 + (Matr4 + 0)) + 1);
    SparseMatrix Matr9(5,5);
    *(1 + *(1 + Matr9 + 1) + 1) = 2;
    const SparseMatrix Matr10(5,5);
    *(1 + *(1 + Matr10 + 1) + 1);
    std::cout <<matrix5[1][1]<<std::endl;
    std::cout <<(Matr4 * Matr4)[1][1]<<std::endl;
    std::cout << *((*(Matr4  + 1)) + 0)<<std::endl;
    std::cout << *((*(matrix5  + 1)) + 0)<<std::endl;
    SparseMatrix M1(3,3);
    SparseMatrix M2(3,3);
    M1 = MakeOnes(3,3);
    M2 = MakeOnes(3,3);
    M1[1][2] = M2[2][1];
    M1[1][1] = M2[0][2];
    SparseMatrix M12(7,7);
    M12[0][0] = M12[1][2];
    return 0;
}
