//
// Created by zeny on 6/4/20.
//

#ifndef COMPILER3PHASES_ACTIONMAKER_H
#define COMPILER3PHASES_ACTIONMAKER_H

#include <bits/stdc++.h>
#include "attribute.h"
using namespace std;

class ActionMaker {
    private:
        int addressCounter;
        int varCounter; 
        unordered_map<string,pair<int,string>> variables;
        void handlePT(vector <attribute>& finalStack);
        void handleDeclaration(vector<attribute>& finalStack, string lex );
        void factor(vector <attribute>& finalStack); 
        string codeOFmulandAdd(string aa, string  bb, string cc1 , string cc2 , string action);
        string addIfByteCode(attribute relop);
        string addIfByteCodeFloat(attribute relop);
        string address_get(string str);

    public:
        void make(string action,vector<attribute>& finalStack, string lex ,  stack<attribute>& s);
        bool isError ;
        string mutibleDef ; 
        ActionMaker();
};


#endif //COMPILER3PHASES_ACTIONMAKER_H
