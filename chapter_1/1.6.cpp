#include <iostream>
using namespace std;

class C{
public:
    int count;
    C(int count = 0){
        this->count = count * 2;
    }
    C(const C &obj){
        count = obj.get() + 10;
    }
    const int get() const{
        return count;
    }
    friend C operator +( C& a, C& b);
};

C operator +(C& a, C& b){
    return C(a.get() + b.get());
}

int main () {
    C c1(7), c2=5, c3(c1+c2);
    cout << c1.get() << c2.get() << c3.get () << endl;
    return 0;
}
