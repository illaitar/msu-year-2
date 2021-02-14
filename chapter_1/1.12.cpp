#include <iostream>
using namespace std;

class I { int i;
public:
    I() : i(5) {
        cout << "fist" << endl;
    }
    I(int a) : i(a) {
        cout << "lance " << i << endl;
    }
    I(const I & other) : i(other.i) {
        cout << "dagger " << i << endl;
    }
    ~I() {
        cout << "pistole" << endl;
    }
    int Get() {
        return i;
    }
    void operator+=(const I & op) {
        i+=op.i;
    }
};
void f(I & x, I y) {
    y += 1000;
    x += y;
}

int main() {
    I i1;
    I i2(30);
    i2 += 700;
    f(i1, i2);
    cout << i1.Get() << ' ' << i2.Get() << endl; return 0;
}

// fist
// lance 30
// lance 700
// pistole
// dagger 730
// lance 1000
// pistole
// pistole
// 1735 730
// pistole
// pistole
