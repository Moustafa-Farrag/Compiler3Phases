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

    /*
        PRIMITIVE_TYPE to PRIMITIVE_TYPE  'id'  ';' 
        DECLARATION to 
                PRIMITIVE_TYPE  'id'   <DECLARATION02> 
        stack         <DECLARATION02>
        final DECLARATION  
        int aa ; 
    */
    if(action.compare("<PRIMITIVE_TYPE10>")==0)
        handlePT(finalStack);
    else if(action.compare("<DECLARATION02>")==0)
        handleDeclaration(finalStack,lex ) ;
}

void ActionMaker::handlePT(vector<attribute> finalStack) {
    attribute a=finalStack.back();
    finalStack.pop_back() ; 
    finalStack.back().type = a.name;
}

void ActionMaker::handleDeclaration(vector<attribute> finalStack, string lex) {
    finalStack.pop_back() ; 
    attribute id = finalStack.back() ;
    finalStack.pop_back() ; 
    attribute pt = finalStack.back() ;
    finalStack.pop_back() ; 
    finalStack.back().type  = pt.type ; 
    finalStack.back().value = id.value ; 
    // -- - --- - -- -
    pair <int , string >  aa = { varCounter++ , pt.type } ;
    variables[id.value] = aa ; 
   // variables
}


