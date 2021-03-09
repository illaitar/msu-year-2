#include <string.h>
#include <iostream>

using std::size_t;

class Tabel{
	size_t *num;
	int *grade;
	int size;
public:
	Tabel(int);
	Tabel(const Tabel &);
	int get(size_t num);
	void set_student(int, int);
	void set_grade(size_t, int);
	int& operator[](const size_t);
	Tabel operator=(const Tabel &);
	const int& operator[](const size_t) const;
	~Tabel();
};

Tabel Tabel::operator=(const Tabel &t){
	if (this == &t)
		throw "self assignment!";
	if (num) delete [] num;
	if (grade) delete [] grade;
	size = t.size;
	num = new size_t[size];
	grade = new int[size];
	memcpy(num, t.num, size);
	memcpy(grade, t.grade, size);
	return *this;
}

void Tabel::set_student(int n, int pos){
	if ((pos > size) || (pos < 0)){
		throw "bad number";
	}
	if (grade[pos] != 0){
		throw "pos is taken";
	}
	num[pos] = n;
}

void Tabel::set_grade(size_t n, int g){
	if ((g < 2) || (g > 5)){
		throw "bad grade";
	}
	int pos = -1;
	for (int i = 0; i < size; ++i){
		if (num[i] == n){
			pos = i;
			break;
		}
	}
	if (pos == -1){
		throw "no such student";
	}
	grade[pos] = g;
}

int Tabel::get(size_t n){
	bool found = false;
	int pos = -1;
	for (int i = 0; i < size; ++i){
		if ((num[i] == n) && (grade[i] != 0)){
			found = true;
			pos = i;
		}
	}
	if (!found){
		throw "bad number";
	}
	return grade[pos];
}

Tabel::Tabel(int s):size(s){
	num = new size_t[size];
	grade = new int[size];
	memset(num, 0, size);
	memset(grade, 0, size);
}

Tabel::Tabel(const Tabel & t){
	size = t.size;
	num = new size_t[size];
	grade = new int[size];
	memcpy(num, t.num, size);
	memcpy(grade, t.grade, size);
}

Tabel::~Tabel(){
	if (num) delete [] num;
	if (grade) delete [] grade;
}

int& Tabel::operator[](const size_t index){
	bool found = false;
	int i;
	for(i=0; i < size; ++i){
		if (num[i] == index){
			found = true;
			break;
		}
	}
	if (!found){
		throw "no such student";
	}
	return grade[i];
}

const int& Tabel::operator[](const size_t index) const {
	bool found = false;
	int i;
	for(i = 0; i < size; ++i){
		if (num[i] == index){
			found = true;
			break;
		}
	}
	if (!found){
		throw "no such student";
	}
	return grade[i];
}

int main(){
	Tabel grades(2180005);
	try {
		grades.set_student(2180001,3);
	}
	catch(char const *c){
		std::cout <<c;
	}
	try{
		grades[2180001] = 3;
	}
	catch( char const *c){
		std::cout <<c;
	}
	std::cout << grades[2180001] << std::endl;

	grades[2180001] = 5;
	return 0;
}
