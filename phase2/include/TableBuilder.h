//
// Created by zeny on 4/15/20.
//

#ifndef UNTITLED_TABLEBUILDER_H
#define UNTITLED_TABLEBUILDER_H
#include <bits/stdc++.h>

using namespace std;

class TableBuilder {

private:
    unordered_map<string,set<string>> first;

    unordered_map<string,set<string>> follow;

    unordered_map<string, set<string>> productions;

    set<string> terminals;

    map<pair<string,string>, string> table;

    void calcTerminals();

    vector<string> tokenize(string s);

    bool isTerminal(string s);

    vector<string> errorMes ; 

void PrintingInOut( int i , stack<string> &s, vector<string> &errorMes, vector<string> &inputWords, string stackP);



public:
    TableBuilder(unordered_map<string, set<string>> first, unordered_map<string, set<string>> follow,
                 unordered_map<string, set<string>> productions);
    void build();
    void lastInput(string s);
    void print();
};


#endif //UNTITLED_TABLEBUILDER_H