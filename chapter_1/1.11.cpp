#include <iostream>
using namespace std;

class I {
    int i;
public:
    I() : i(6) { cout << "owl" << endl; }
    I(int a) : i(a) { cout << "sheep " << i << endl; }
    I(const I & other) : i(other.i) { cout << "horse " << i << endl; } ~I() { cout << "wolf" << endl; }
    int Get() { return i; }
    void operator*=(const I & op) { i*=op.i; }
};

void f(I x, I & y) { x *= 1;
    y *= x;
}

int main() {
    I i1;
    I i2(3);
    i1 *= 7;
    f(i1, i2);
    cout << i1.Get() << ' ' << i2.Get()<< endl;
    return 0;
}

// owl
// sheep 3
// sheep 7
// wolf
// horse 42
// sheep 1
// wolf
// wolf
// 42 126
// wolf
// wolf
