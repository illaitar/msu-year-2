//суть в том что мы перегружаем оператор new
#include <iostream>
using namespace std;


class smartstr
{
private:
    void * operator new[](size_t size);
};



int main(){
    //smartstr* nc = new smartstr[10]; - не сработает как раз потому что new[] перегружен
    smartstr* nc = new smartstr; //сработало
    return 0;
}
