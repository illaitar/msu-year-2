#include <iostream>
using namespace std;

struct mystr {
private:
    mystr(){}
    mystr(const mystr&){}
    mystr operator =(const mystr&);
    mystr operator = (mystr&);
    int a, b;
};

int f(mystr s) {
    return 0;
}

int i = sizeof(mystr);

int main(){
    return 0;
}
