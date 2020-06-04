//
// Created by zeny on 6/4/20.
//

#include "../include/ActionMaker.h"
//unordered_map<string,pair<int,string>> variables;
ActionMaker::ActionMaker(){
    addressCounter=0;
    varCounter=1;
}

void ActionMaker::make(string action, vector<attribute> finalStack, string lex , stack<attribute> s ) {
    if(action.compare("<PRIMITIVE_TYPE10>")==0)
        handlePT(finalStack);
    else if(action.compare("<DECLARATION01>")==0)
        handleDeclaration(finalStack,lex ) ;
}

void ActionMaker::handlePT(vector<attribute> finalStack) {
    attribute a=finalStack.back();
    finalStack.back().type=a.name;
}

void ActionMaker::handleDeclaration(vector<attribute> finalStack, string lex) {
    attribute a=finalStack.end()[-2];
    finalStack.back().type=a.type;
    pair<int,string>p;
    p.first=varCounter++;
    p.second=a.type;
    variables[lex]=p;
}


