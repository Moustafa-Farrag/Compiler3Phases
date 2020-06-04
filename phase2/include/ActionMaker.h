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
        int addressCounter;
        int varCounter;
        unordered_map<string,pair<int,string>> variables;
        void handlePT(vector<attribute> finalStack);
        void handleDeclaration(vector<attribute> finalStack, string lex);
    public:
        void make(string action,vector<attribute> finalStack, string lex);
        ActionMaker();
};


#endif //COMPILER3PHASES_ACTIONMAKER_H
