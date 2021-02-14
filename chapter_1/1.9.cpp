#include <iostream>
using namespace std;

class C{
public:
    int count;
    C(int count = 0){
        this->count = count * 2;
    }
    friend C& operator +(const C& b);

    int get() const{
        return count;
    }
};

C operator +(const C& b1,const C& b2){
    return C(b1.get() + b2.get());
}

int main () {
    C c1(7) /*,c2 = 5*/, c3(c1 + c1);
    cout << c1.get ( ) << ' ' << c3.get ( ) << endl; return 0;
}
