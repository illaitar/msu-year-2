#include <iostream>
using namespace std;

class A{
    int a;
public:
    A(int a = 0){
        this->a = a;
    }
    A(const A & obj ){
        this->a = obj.a;
    }
    int get() const{
        return a;
    }
    A& operator *=(int b){
        this->a *= b;
        return *this;
    }
    A& operator *=(const A& b){
        this->a *= b.get();
        return *this;
    }
};

int main () {
    A a1(5), a2=3;
    a1 *= 10;
    a2 *= a1 *= 2;
    cout << a1.get() << a2.get() << endl;
    return 0;
}

//ответ 100300
