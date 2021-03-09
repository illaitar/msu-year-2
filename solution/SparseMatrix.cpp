#include <cstring>
#include "SparseMatrix.hpp"
#include <iostream>

using std::size_t;

double SparseMatrix::epsilon = 1e-8;

/*    SparseMatrix     */
SparseMatrix::~SparseMatrix(){
    free(first);
    free(second);
    delete[] third;
};

ProxyOne
SparseMatrix::operator+ (const size_t index) {
    return ProxyOne(this, index);
}

ProxyOne
SparseMatrix::operator- (const size_t index) {
    return ProxyOne(this, -index);
}

ProxyOneConst
SparseMatrix::operator+ (const size_t index) const{
    return ProxyOneConst(this, index);
}

ProxyOneConst
SparseMatrix::operator- (const size_t index) const{
    return ProxyOneConst(this, -index);
}

ProxyTwo
SparseMatrix::operator[] (const size_t index) {
    return ProxyTwo(this, index);
}

ProxyTwoConst
SparseMatrix::operator[] (const size_t index) const{
    return ProxyTwoConst(this, index);
}

ProxyTwoConst
SparseMatrix::operator* () const{
    return ProxyTwoConst(this, 0);
}

ProxyTwo
SparseMatrix::operator* (){
    return ProxyTwo(this, 0);
}

SparseMatrix&
SparseMatrix::operator=(const SparseMatrix &m){
    if (this == &m)
        throw "self assignment";
    if (m.third == nullptr){
        if (first) free(first);
        if (second) free(second);
        if (third) delete[] third;
        first = nullptr;
        second = nullptr;
        third = nullptr;
        return *this;
    }
    if ((this->size_x != m.size_x) || (this->size_y != m.size_y))
        throw "size mismatch";
    int num = m.third[size_y];
    first = (double*) malloc(sizeof(double) * num);
    second = (size_t*) malloc(sizeof(size_t) * num);
    third = new size_t[size_y + 1]();
    memcpy(first,m.first,num * sizeof(double));
    memcpy(second,m.second,num * sizeof(size_t));
    memcpy(third,m.third,(size_y + 1) * sizeof(size_t));
    return *this;
}

bool
SparseMatrix::operator==(const SparseMatrix &m){
    if (m.third == nullptr){
        if (third == nullptr)
            return true;
        return false;
    }
    if ((m.size_x != size_x) || (m.size_y != size_y))
        return false;
    if (m.third[size_y] != third[size_y])
        return false;
    for (size_t i = 0; i < third[size_y]; ++i)
        if ((first[i] - m.first[i] > epsilon) || (first[i] - m.first[i] < -epsilon))
            return false;
    return true;
}

bool
SparseMatrix::operator!=(const SparseMatrix &m){
    return !(*this == m);
}

double*
SparseMatrix::checkElem(const size_t x, const size_t y) const{
    if ((x >= size_x) || (y >= size_y))
        throw "bad index";
    if (third == NULL)
        return NULL;
    double *ptr = NULL;
    for (size_t i = 0; (i < third[y+1] - third[y]) && (second[third[y] + i] <= x); ++i)
        if (second[third[y] + i] == x){
            ptr = &(first[third[y] + i]);
            break;
        }
    return ptr;
}

void
SparseMatrix::set(const size_t x, const size_t y, double value, int mode){
    if ((x >= size_x) || (y >= size_y))
        throw "bad index";
    if (third == nullptr){
        actual_size = 100;
        first = (double*) malloc(sizeof(double) * 100);
        first[0] = value;
        second = (size_t*) malloc(sizeof(size_t) * 100);
        second[0] = x;
        third = new size_t[size_y + 1]();
        for (size_t i = y + 1; i < size_y + 1; ++i)
            third[i] = 1;
        return;
    }
    double *val;
    if ((val = checkElem(x, y)) != NULL){
        if (mode != 0)
            *val += value;
        else
            *val = value;
        return;
    }
    size_t pos, i;
    for (i = 0; (i < third[y+1] - third[y]) && (x >= second[third[y] + i]); ++i);
    pos = i;
    if (third[size_y]+1 > actual_size){
        first = (double*) realloc (first, (third[size_y]+1 + 100) * sizeof(double));
        second = (size_t*) realloc (second, (third[size_y]+1 + 100) * sizeof(size_t));
    }
    for (i = third[y] + pos + 1; i < third[size_y] + 1; ++i){
        first[i] = first[i-1];
        second[i] = second[i-1];
    }
    first[third[y] + pos] = value;
    second[third[y] + pos] = x;
    for (size_t n = y + 1; n < size_y + 1; ++n)
        third[n] += 1;
}

double
SparseMatrix::get(const size_t x, const size_t y) const {
    double *val = checkElem(x, y);
    if (val != NULL)
        return *val;
    return 0;
}

SparseMatrix::SparseMatrix(const SparseMatrix &m) :size_x(m.size_x),size_y(m.size_y) {
    if (m.third == nullptr){
        first = nullptr;
        second = nullptr;
        third = nullptr;
        return;
    }
    size_t num = m.third[size_y];
    actual_size = num + 100;
    first = (double*) malloc ((num+100) * sizeof(double));
    second = (size_t*) malloc ((num+100) * sizeof(size_t));
    third = new size_t[size_y + 1]();
    memcpy(first,m.first,num * sizeof(double));
    memcpy(second,m.second,num * sizeof(size_t));
    memcpy(third,m.third,(size_y + 1) * sizeof(size_t));
};

SparseMatrix::SparseMatrix(const size_t x_s, const size_t y_s):size_x(x_s),size_y(y_s){
    first = nullptr;
    second = nullptr;
    third = nullptr;
    actual_size = 0;
};

ProxyOne
operator+(const size_t i, SparseMatrix &m){
    return ProxyOne(&m,i);
}

ProxyOneConst
operator+(const size_t i, const SparseMatrix &m){
    return ProxyOneConst(&m,i);
}

SparseMatrix
operator+(const SparseMatrix &m1, const SparseMatrix &m2){
    if ((m1.num_columns() != m2.num_columns()) || (m1.num_rows() != m2.num_rows()))
        throw "size mismatch";
    SparseMatrix m3(m1.size_x, m1.size_y);
    m3 = m1;
    size_t k = 0;
    for (size_t i = 0; i < m2.third[m1.size_y];++i){
        while (i >= m2.third[k + 1])
            k++;
        m3.set(m2.second[i],k, m2.first[i],1);
    }
    return m3;
}

SparseMatrix
operator*(const SparseMatrix &m1, const SparseMatrix &m2){
    SparseMatrix m3(m1.size_x, m1.size_y);
    double *result = new double[m2.size_y]();
    double *d = new double[m2.size_y]();
    for (size_t nz = 0; nz < m2.size_x; nz++){
        for (size_t z = 0; z<m2.size_y;++z)
            d[z] = m2.get(nz,z);
        size_t i, k;
        for (i = 0; i < m1.size_y; i = i + 1)
            for (k = m1.third[i]; k < m1.third[i+1]; k = k + 1)
                result[i] = result[i] + m1.first[k]*d[m1.second[k]];
        for (size_t af = 0; af < m2.size_y; af++)
            if (!((result[af] <=0.0001) && (result[af] >= -0.0001))){
                m3.set(nz,af,result[af],0);
                result[af] = 0;
            }
    }
    delete [] result;
    delete [] d;
    return m3;
}

/* ProxyOne */

ProxyTwo
ProxyOne::operator*(){
    return ProxyTwo(matr, index1);
}

ProxyOne
operator+(const int index, const ProxyOne &p2){
    return ProxyOne(p2.matr,p2.index1 + index);
}

ProxyOne&
ProxyOne::operator + (const size_t i){
    index1 += i;
    return *this;
}

ProxyOne&
ProxyOne::operator- (const size_t i){
    index1 -= i;
    return *this;
}
/* ProxyOneConst */
ProxyOneConst
operator+(const int index, const ProxyOneConst &p2){
    return ProxyOneConst(p2.matr,p2.index1 + index);
}

ProxyOneConst&
ProxyOneConst::operator+ (const size_t i){
    index1 += i;
    return *this;
}

ProxyOneConst&
ProxyOneConst::operator- (const size_t i){
    index1 -= i;
    return *this;
}

ProxyTwoConst
ProxyOneConst::operator*(){
    return ProxyTwoConst(matr, index1);
}

/* ProxyTwo */

ProxyTwo
operator+(const int index, const ProxyTwo &p2){
    return ProxyTwo(p2.matr,p2.index1, p2.index2 + index);
}

ProxyTwo&
ProxyTwo::operator+ (const size_t i){
    index2 += i;
    return *this;
}

ProxyTwo&
ProxyTwo::operator- (const size_t i){
    index2 -= i;
    return *this;
}

double&
ProxyTwo::operator*(){
    double *ptr = (*matr).checkElem(index1, index2);
    if (ptr == NULL){
        (*matr).set(index1, index2, 0, 2);
        ptr = (*matr).checkElem(index1, index2);
    }
    double &ret = *ptr;
    return ret;
}

double&
ProxyTwo::operator[](const int index){
    double *ptr = (*matr).checkElem(index1, index2+index);
    if (ptr == NULL){
        (*matr).set(index1, index2+index, 0, 2);
        ptr = (*matr).checkElem(index1, index2 + index);
    }
    double &ret = *ptr;
    return ret;
}

/* ProxyTwoConst */
ProxyTwoConst&
ProxyTwoConst::operator+ (const size_t i){
    index2 += i;
    return *this;
}

ProxyTwoConst&
ProxyTwoConst::operator- (const size_t i){
    index2 -= i;
    return *this;
}

ProxyTwoConst
operator+(const int index, const ProxyTwoConst &p2){
    return ProxyTwoConst(p2.matr,p2.index1, p2.index2 + index);
}

double
ProxyTwoConst::operator*(){
    double *ptr = (*matr).checkElem(index1, index2);
    if (ptr == NULL)
        return 0;
    return *((*matr).checkElem(index1, index2));
}

double
ProxyTwoConst::operator[](const int index){
    double *ptr = (*matr).checkElem(index1, index2 + index);
    if (ptr == NULL)
        return 0;
    return *((*matr).checkElem(index1, index2 + index));
}
