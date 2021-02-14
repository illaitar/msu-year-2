#include <fstream>
#include <iostream>
using namespace std;

class A {
public: A(int c = 0){
    cout << "A ";
}

};
class B : public A {
    public:
        B(int c = 0){cout << "B ";}


};


class C : public B {public: C(int c = 0){cout << "C ";}};

int main(){
    C c;
A a = c; struct D {
B b;
D(): b(5){} } d;
}
