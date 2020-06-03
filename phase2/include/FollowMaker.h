//
// Created by Ahmed on 4/15/2020.
//

#ifndef UNTITLED_FOLLOWMAKER_H
#define UNTITLED_FOLLOWMAKER_H

#include <bits/stdc++.h>

using namespace std;

class FollowMaker {

private:

    unordered_map<string, set<string>> Follow;
    unordered_map<string, set<string>> First;

    unordered_map<string, set<string>> Productions;

    string start;

    vector<string> tokenize(string s);

    void calcLanguage();

    bool isTerminal(string s);

    bool isNotTerminal(string s);

public:
    FollowMaker(unordered_map<string, set<string>> productions,
                unordered_map<string, set<string>> first);

    void make();

    void setStart(string start);

    unordered_map<string, set<string>> getFollow();

    void setFollow(unordered_map<string, set<string>> f);
    
    void print();

//    const set<string> &getLanguage() const;
//
//    void setLanguage(const set<string> &language);
};


#endif //UNTITLED_FOLLOWMAKER_H
