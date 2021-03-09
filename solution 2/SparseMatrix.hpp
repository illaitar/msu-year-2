#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include <algorithm>

using std::size_t;

 //main class
class SparseMatrix;

 //classes for address arithmetics
class ProxyOne;
class ProxyTwo;
class ProxyOneConst;
class ProxyTwoConst;

class ProxyOne{
    SparseMatrix *matr;
    size_t index1;

    ProxyOne(SparseMatrix *m, size_t i):matr(m), index1(i){};
    ProxyOne(const ProxyOne & m):matr(m.matr),index1(m.index1) {}
public:
    friend class SparseMatrix;
    friend class ProxyTwo;

    friend ProxyOne operator+(const int index, const ProxyOne &p2);
    friend ProxyOne operator+(const size_t i, SparseMatrix &m);
    friend ProxyOne operator-(const size_t i, SparseMatrix &m);

    ProxyOne& operator+ (const size_t i);
    ProxyOne& operator- (const size_t i);
    ProxyTwo operator*();
};

class ProxyOneConst{
    const SparseMatrix *matr;
    size_t index1;

    ProxyOneConst(const SparseMatrix *m, size_t i):matr(m), index1(i){};
    ProxyOneConst(const ProxyOneConst & m):matr(m.matr),index1(m.index1) {}
public:
    friend class ProxyTwoConst;
    friend class SparseMatrix;

    friend ProxyOneConst operator+(const int index, const ProxyOneConst &p2);
    friend ProxyOneConst operator+(const size_t i, const SparseMatrix &m);

    ProxyOneConst& operator+ (const size_t i);
    ProxyOneConst& operator- (const size_t i);
    ProxyTwoConst operator*();
};

class ProxyTwo{
    SparseMatrix *matr;
    size_t index1, index2;

    ProxyTwo(SparseMatrix *m, size_t i1, size_t i2 = 0):matr(m), index1(i1), index2(i2) {};
    ProxyTwo(const ProxyTwo & m):matr(m.matr),index1(m.index1), index2(m.index2){}
public:
    friend class ProxyOne;
    friend class SparseMatrix;

    friend ProxyTwo operator+(const int index, const ProxyTwo &p2);

    ProxyTwo& operator+ (const size_t i);
    ProxyTwo& operator- (const size_t i);
    double& operator*();
    double& operator[](const int index);
};

class ProxyTwoConst{
    const SparseMatrix *matr;
    size_t index1, index2;

    ProxyTwoConst(const SparseMatrix *m, size_t i1, size_t i2 = 0):matr(m), index1(i1), index2(i2) {};
    ProxyTwoConst(const ProxyTwoConst & m):matr(m.matr),index1(m.index1), index2(m.index2){}
public:
    friend class ProxyOneConst;
    friend class SparseMatrix;

    friend ProxyTwoConst operator+(const int index, const ProxyTwoConst &p2);

    ProxyTwoConst& operator+ (const size_t i);
    ProxyTwoConst& operator- (const size_t i);
    double operator*();
    double operator[](const int index);
};

class SparseMatrix{
    double *first;
    size_t *second, *third;
    size_t init_size, actual_size;
    const size_t size_x, size_y;
    double* checkElem(const size_t x, const size_t y) const;

public:
    static double epsilon;
    SparseMatrix(const SparseMatrix &m);
    SparseMatrix(const size_t x_s, const size_t y_s);

    friend class ProxyOne;
    friend class ProxyOneConst;
    friend class ProxyTwo;
    friend class ProxyTwoConst;

    friend SparseMatrix  operator+(const SparseMatrix &m1, const SparseMatrix &m2);
    friend SparseMatrix  operator*(const SparseMatrix &m1, const SparseMatrix &m2);
    friend ProxyOne      operator+(const size_t i, SparseMatrix &m);
    friend ProxyOneConst operator+(const size_t i, const SparseMatrix &m);
    friend ProxyOneConst operator-(const size_t i, const SparseMatrix &m);

    inline size_t num_columns()            const {return size_x;};
    inline size_t num_rows()               const {return size_y;};
    static inline void   set_epsilon(double eps) {epsilon = eps;};

    double get(const size_t x, const size_t y) const;
    void   set(const size_t x, const size_t y, double value, int mode = 0);

    SparseMatrix& operator=(const SparseMatrix &m);
    bool          operator==(const SparseMatrix &m);
    bool          operator!=(const SparseMatrix &m);

    ProxyOne      operator+ (const size_t index);
    ProxyOneConst operator+ (const size_t index) const;
    ProxyOne      operator- (const size_t index);
    ProxyOneConst operator- (const size_t index) const;
    ProxyTwo      operator[] (const size_t index);
    ProxyTwoConst operator[] (const size_t index) const;
    ProxyTwo      operator* ();
    ProxyTwoConst operator* () const;

    virtual ~SparseMatrix();
};

//Fabric Functions
inline SparseMatrix MakeOnes(size_t x, size_t y){
    SparseMatrix M(x,y);
    for (size_t i = 0; i < std::min(x,y); ++i)
        M.set(i,i,1.0);
    return M;
}

#endif
