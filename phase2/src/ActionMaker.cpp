//
// Created by zeny on 6/4/20.
//

#include "../include/ActionMaker.h"
//unordered_map<string,pair<int,string>> variables;
ActionMaker::ActionMaker(){
    addressCounter=0;
    varCounter=1;
}

void ActionMaker::make(string action, vector<attribute>& finalStack, string lex , stack<attribute>& s ) {

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
    else if (action == "<FACTOR10>" || action == "<FACTOR20>" ) {
        factor(finalStack) ;
    }else if (action == "<TERM00>" ||  action == "<SIMPLE_EXPRESSION10>" || action == "<EXPRESSION00>" ) {
       attribute aa = finalStack.back() ; 
        for ( int i = 0 ; i < aa.code.size() ; i++) {
            cout << aa.code[i] << " aa00"<< endl ; 
            s.top().code.push_back(aa.code[i]);
        }

    }else if (action == "<TERM'01>" || action == "<SIMPLE_EXPRESSION'01>"  ) {
        attribute aa = finalStack.back() ; 
        finalStack.pop_back();
        cout << aa.name << endl ; 
        attribute cc = finalStack.back() ; 
        finalStack.pop_back();  
        cout << cc.name << endl ;
        attribute bb = finalStack.back() ; 
        finalStack.pop_back(); 
        cout << bb.name << endl ;
        finalStack.push_back(bb);
        finalStack.push_back(cc);
        finalStack.push_back(aa);

        for ( int i = 0 ; i < bb.code.size() ; i++) {
            cout << bb.code[i] << " bb"<< endl ; 
            s.top().code.push_back(bb.code[i]);
        }
        for ( int i = 0 ; i < aa.code.size() ; i++) {

            cout << aa.code[i] << " aa"<< endl ; 
            s.top().code.push_back(aa.code[i]);
        }
       // s.top().code.insert(s.top().code.end(), aa.code.begin(), aa.code.end());
        // s.top().code.insert(s.top().code.end(), bb.code.begin(), bb.code.end());
        for ( int i = 0 ; i <  s.top().code.size() ; i++) {
            cout << s.top().code[i] << " ss" << endl ; 
        }
       if ( action ==  "<TERM'01>" ) {
         s.top().code.push_back("imul") ;
       } else {
         s.top().code.push_back("iadd") ;
       }

    }else if ( action == "<TERM'02>" || action == "<SIMPLE_EXPRESSION'02>"){
        attribute aa = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.back().code = aa.code ; 
    } else if ( action == "<TERM01>" || action == "<SIMPLE_EXPRESSION11>" || action == "<EXPRESSION01>" ) {
        attribute temp = finalStack.back(); 
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.back().code = temp.code ; 
    } else if (action == "<ASSIGNMENT03>" ) 
    {
        // ASSIGNMENT 'id' 'assign' EXPRESSION ';' 
        attribute Coma = finalStack.back(); 
        finalStack.pop_back() ; 
        attribute Ex = finalStack.back(); 
        finalStack.pop_back() ; 
        attribute Assing = finalStack.back(); 
        finalStack.pop_back() ; 
        attribute Id = finalStack.back(); 
        finalStack.pop_back() ; 
        finalStack.back().code = Ex.code ; 
        finalStack.back().code.push_back("iload num") ;
        /* code */
    } if ( action == "<STATEMENT00>" ) {
        cout << "finshed........" << endl  ; 
        attribute Assigin = finalStack.back(); 
        finalStack.pop_back() ; 
        finalStack.back().code = Assigin.code ; 
    }
    

}

void ActionMaker::handlePT(vector<attribute>& finalStack) {
    attribute a=finalStack.back();
    cout << finalStack.size() << endl ;
    finalStack.pop_back() ; 
        cout << finalStack.size() << endl ;
    finalStack.back().type = a.value;
    cout << "lllllllllllllll" << endl ; 
}

void ActionMaker::handleDeclaration(vector<attribute>& finalStack, string lex) {
    cout << "hhhhhhhhhhhhhhhhhh" << endl ; 
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

void ActionMaker::factor(vector<attribute>& finalStack) {

    attribute numOrID = finalStack.back();
    finalStack.pop_back();  

    if ( numOrID.name == "\'num\'" ){
        string ad= to_string(addressCounter)+": ";
        addressCounter+=2;
        string code1 = ad +"bipush " + numOrID.value ;
        finalStack.back().code.push_back(code1) ;
        finalStack.back().value = numOrID.value ; 
    }
    else {
        //serch in table
        string ad= to_string(addressCounter)+": ";
        addressCounter+=2;
        string code1 = ad+"bipush " + numOrID.value ; // will change
        finalStack.back().code.push_back(code1) ;
        finalStack.back().value = numOrID.value ; 
    }
}


