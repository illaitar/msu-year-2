#include <iostream>
using namespace std;

class A{
    char a;
    int b, c;
public:
    A(char a = '0', int b = 0, int c = 0){
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

int main(){
    A b(1);
    A c(1, 2);
    A d('1', 1);
    return 0;
}
