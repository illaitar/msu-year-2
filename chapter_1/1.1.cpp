#include <iostream>
using namespace std;


class A {
    int a, b;
public:
    A (const A & x) { //если не поставить const то временно созданные объекты вызовут ошибку
        a = x.a;
        b = x.b;
        cout << 1;
    }
    A (int a = 0, int b = 0){ //без значений по умолчанию сломается строка 23 например
        this -> a = a;
        b = a;
        cout << 2;
    }
};


void f () {
    A x (1);
    A y;
    A z = A (2.5, 4);
    A s = 6; //временно созданный объект
    A w = z;
    x = z = w;
}

int main(){
    f();
}
