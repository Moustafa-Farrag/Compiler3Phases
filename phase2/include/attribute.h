#include <iostream>
#include <vector> 
#include <string.h>

using namespace std;

class attribute
{
private:
    
    string value ; 
    string type ; 
    string  code ; 
    vector <int> trueList ; 
    vector <int> flaseList; 
    

public:
    attribute(/* args */);
    ~attribute();
};

attribute::attribute(/* args */)
{
}

attribute::~attribute()
{
}
