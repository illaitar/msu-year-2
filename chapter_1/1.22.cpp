#include <fstream>
#include <iostream>
using namespace std;

class Graph{

};

class IReadGraph{
protected:
    virtual Graph openFile(const char *filename) = 0;
    virtual bool readGraph(const char *errorMessage) = 0;

    virtual ~IReadGraph() {};
};

class ReadGraphFile: public IReadGraph{
public:
	Graph openFile(const char *filename) override{
		std::ifstream fin(filename);
		return Graph();
	}
};

int main(){
	return 0;
}
