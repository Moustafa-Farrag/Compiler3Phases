#ifndef TOKEN_H
#define TOKEN_H


#include <bits/stdc++.h>

using namespace std;

class Token {
public:
    Token();

    virtual ~Token();

    Token(string name);

    Token(string name, string pattern, int priority);

    string getName();

    void setName(string name);

    string getPattern();

    void setPattern(string pattern);

    int getPriority();

    void setPriority(int priority);

protected:

private:
    string name;
    string pattern;
    int priority;
};

#endif // TOKEN_H
