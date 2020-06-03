//
// Created by zeny on 4/12/20.
//

#ifndef UNTITLED_FIRSTMAKER_H
#define UNTITLED_FIRSTMAKER_H

#include <bits/stdc++.h>
using namespace std;

class FirstMaker {

private:

    unordered_map<string,set<string>> F;

    unordered_map<string, set<string>>& Productions;

    set<string> language;

    vector<string> tokenize(string s);

    void calcLanguage();

    bool isTerminal(string s);

public:
    FirstMaker(unordered_map<string, set<string>> &productions);

    void make();

    const unordered_map<string,set<string>>  &getF() const;

    void setF(const unordered_map<string,set<string>>  &f);

    const set<string> &getLanguage() const;

    void setLanguage(const set<string> &language);

    void printin() ; 

};


#endif //UNTITLED_FIRSTMAKER_H
