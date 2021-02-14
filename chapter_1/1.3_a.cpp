#include <iostream>
using namespace std;

class X {
    int i;
    double t;
    // X(int k) {
    //     i = k;
    //     t = 0;
    //     cout << 1;
    // }
    //здесь проблема в том, что этот конструктор доступен только методам класса
public:
    X(int k, double r = 0) {
        i = k;
        t = r;
        cout << 2;
    }
    X & operator= (X & a) {
        i = a.i;
        t = a.t;
        cout << 3;
        return * this;
    }
    X(const X & a) {
        i = a.i;
        t = a.t;
        cout << 4;
    }
};

int main() {
    // X a; нет соответствующего конструктора
    X b(1);
    X c (2, 3.5);
    X d = c;
    X e (6.5, 3);
    c = d = e;
}

//ответ 224233
