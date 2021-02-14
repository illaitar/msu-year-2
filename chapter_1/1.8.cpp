#include <iostream>
using namespace std;

class B{
public:
    int count;
    B(int count = 0, int add = 5){
        this->count = count + add;
    }
    B& operator +=(int b){
        this->count += b;
        return *this;
    }
    B& operator +=(const B& b){
        this->count += b.get();
        return *this;
    }
    int get() const{
        return count;
    }
};

int main () {
    B b1 (1), b2(2,3), b3 (b1);
    b1 += b2 += b3;
    cout << b1.get() << ' ' << b2.get() << ' ' << b3.get () << endl; return 0;
}
