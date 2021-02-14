#include <iostream>
using namespace std;

class B{
public:
    int count = 10;
    B(){}
    B(B &obj){
        count = obj.get() + 10;
    }
    const int get(){
        return count;
    }
};

int main () {
    B b1, b2=b1, b3(b2);
    cout << b1.get() << b2.get() << b3.get () << endl;
    return 0;
}
