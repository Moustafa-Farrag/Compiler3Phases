//
// Created by zeny on 6/4/20.
//

#ifndef COMPILER3PHASES_ACTIONMAKER_H
#define COMPILER3PHASES_ACTIONMAKER_H

#include <bits/stdc++.h>
#include <attribute.h>
using namespace std;

class ActionMaker {
    private:
        unordered_map<string,pair<int,string>> variables;
    public:
        void make(vector<attribute> finalStack, string lex);
}


#endif //COMPILER3PHASES_ACTIONMAKER_H
