#include <iostream>
using namespace std;

class A{
public:
    int count;
    A(int count = 7){
        this->count = count ;
    }
    A& operator *=(int b){
        this->count *= b;
        return *this;
    }
    A& operator *=(const A& b){
        this->count *= b.get();
        return *this;
    }
    int get() const{
        return count;
    }
};

int main () {
    A a1(5), a2 = 4, a3;
    a2 *= a1 *= 3;
    cout << a1.get( ) << ' ' << a2.get() << ' ' << a3.get( ) << endl;
    return 0;
}
