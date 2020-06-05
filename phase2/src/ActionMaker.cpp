//
// Created by zeny on 6/4/20.
//

#include "../include/ActionMaker.h"
//unordered_map<string,pair<int,string>> variables;
ActionMaker::ActionMaker()
{
    addressCounter = 0;
    varCounter = 1;
}

void ActionMaker::make(string action, vector<attribute> &finalStack, string lex, stack<attribute> &s)
{

    /*
        PRIMITIVE_TYPE to PRIMITIVE_TYPE  'id'  ';' 
        DECLARATION to 
                PRIMITIVE_TYPE  'id'   <DECLARATION02> 
        stack         <DECLARATION02>
        final DECLARATION  
        int aa ; 
    */
    if (action.compare("<PRIMITIVE_TYPE10>") == 0)
    {
        handlePT(finalStack);
    }
    else if (action.compare("<DECLARATION02>") == 0)
    {
        handleDeclaration(finalStack, lex);
    }
    else if (action == "<FACTOR10>" || action == "<FACTOR20>")
    {
        factor(finalStack);
    }
    else if (action == "<TERM00>" || action == "<SIMPLE_EXPRESSION10>" || action == "<EXPRESSION00>")
    {
        attribute aa = finalStack.back();
        for (int i = 0; i < aa.code.size(); i++)
        {
            // cout << aa.code[i] << " aa00" << endl;
            s.top().code.push_back(aa.code[i]);
        }

        cout << "---------++-------++--" << endl ; 
        cout << action << " " << aa.type << " " << aa.value << aa.name << endl ;
        cout << "---------++----------++-" << endl ;

        s.top().type = aa.type;
        s.top().value = aa.value;
    }
    else if (action == "<TERM'01>" || action == "<SIMPLE_EXPRESSION'01>")
    {
        // 'mulop' <TERM'00> FACTOR <TERM'01> TERM' <TERM'02>

        attribute aa = finalStack.back();
        finalStack.pop_back();
        cout << aa.name << endl;
        attribute cc = finalStack.back();
        finalStack.pop_back();
        cout << cc.name << endl;
        attribute bb = finalStack.back();
        finalStack.pop_back();
        cout << bb.name << endl;
        finalStack.push_back(bb);
        finalStack.push_back(cc);
        finalStack.push_back(aa);

        for (int i = 0; i < bb.code.size(); i++)
        {
            s.top().code.push_back(bb.code[i]);
        }
        for (int i = 0; i < aa.code.size(); i++)
        {
            s.top().code.push_back(aa.code[i]);
        }

      /*  for (int i = 0; i < s.top().code.size(); i++)
        {
            cout << s.top().code[i] << " ss" << endl;
        }*/

      /*  cout << "**************************" << endl;

        cout << aa.type << " " << bb.type << " " << cc.type << endl;
        cout << aa.name << " " << bb.name << " " << cc.name << endl;
        cout << aa.value << " " << bb.value << " " << cc.value << endl;

        cout << "***********************++++" << endl;
        */
        s.top().type = aa.type ; 
        s.top().value = "non" ;
        string ad = to_string(addressCounter++) + ": "+ codeOFmulandAdd(aa.type, bb.type, cc.value , cc.name , action);
        s.top().code.push_back(ad);

    }
    else if (action == "<TERM'02>" || action == "<SIMPLE_EXPRESSION'02>")
    {
        attribute aa = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.back().code = aa.code;
        finalStack.back().type = aa.type;
        finalStack.back().value = aa.value;
    }
    else if (action == "<TERM01>" || action == "<SIMPLE_EXPRESSION11>" || action == "<EXPRESSION01>" || action == "<EXPRESSION001>")
    {
        attribute temp = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        for(auto i : temp.code)
            finalStack.back().code.push_back(i);
        finalStack.back().type = temp.type;
        finalStack.back().value = temp.value;
    }
    else if (action == "<ASSIGNMENT03>")
    {
        // ASSIGNMENT 'id' 'assign' EXPRESSION ';'
        attribute Coma = finalStack.back();
        finalStack.pop_back();
        attribute Ex = finalStack.back();
        finalStack.pop_back();
        attribute Assing = finalStack.back();
        finalStack.pop_back();
        attribute Id = finalStack.back();
        finalStack.pop_back();
        finalStack.back().code = Ex.code;
        if ( Ex.type == "\'float\'" ){
            string ad = to_string(addressCounter++) + ": ";
            finalStack.back().code.push_back(ad+"fload num");
        } else if ( Ex.type == "\'float\'" ) {
            string ad = to_string(addressCounter++) + ": ";
            finalStack.back().code.push_back("ad+iload num");
        }
        /* code */
    }
    else if (action == "<STATEMENT00>" || action == "<STATEMENT10>" || action == "<STATEMENT20>" || action == "<STATEMENT30>")
    {
        cout << "finshed........" << endl;
        attribute Assigin = finalStack.back();
        finalStack.pop_back();
        finalStack.back().code = Assigin.code;
    }else if (action == "<IF04>" ){
        finalStack.pop_back() ;
        finalStack.pop_back() ;
        attribute temp = finalStack.back();
        finalStack.pop_back() ;
        finalStack.pop_back() ;
        finalStack.pop_back() ;
        finalStack.back().trueList.push_back(addressCounter)  ;
        string ad= to_string(addressCounter)+": ";
        addressCounter+=3;
        finalStack.back().code=temp.code;
        finalStack.back().code.push_back(ad +"if_icmplt");
    }else if (action == "<IF06>" ){
        finalStack.pop_back() ;
        attribute st=finalStack.back();
        finalStack.pop_back() ;
        finalStack.back().flaseList.push_back(addressCounter)  ;
        string ifIns =finalStack.back().code.back()+"   "+to_string(addressCounter);
        finalStack.back().code.pop_back();
        finalStack.back().code.push_back(ifIns);
        for(auto i:st.code)
            finalStack.back().code.push_back(i);
    }
}

void ActionMaker::handlePT(vector<attribute> &finalStack)
{
    attribute a = finalStack.back();
    cout << finalStack.size() << endl;
    finalStack.pop_back();
    cout << finalStack.size() << endl;
    finalStack.back().type = a.value;
}

void ActionMaker::handleDeclaration(vector<attribute> &finalStack, string lex)
{

    //DECleration ->>  PRIMITIVE_TYPE <DECLARATION00> 'id' <DECLARATION01> ';' <DECLARATION02> 
    finalStack.pop_back();  //  ; 
    attribute id = finalStack.back();
    finalStack.pop_back();
    attribute pt = finalStack.back();
    finalStack.pop_back();
    finalStack.back().type = pt.type;
    finalStack.back().value = id.value;
    // -- - --- - -- -
    pair<int, string> aa = {varCounter++, pt.type};
    variables[id.value] = aa;
    // variables
}

void ActionMaker::factor(vector<attribute> &finalStack)
{

    attribute numOrID = finalStack.back();
    finalStack.pop_back();

    if (numOrID.name == "\'num\'")
    {
        string ad = to_string(addressCounter) + ": ";
        addressCounter += 2;
        
        finalStack.back().value = numOrID.value;
        if (numOrID.value.find(".") != std::string::npos) {
            finalStack.back().type = "\'float\'"; // will change
            string code1 = ad + "bfpush " + numOrID.value;
            finalStack.back().code.push_back(code1);
        }else {
            finalStack.back().type = "\'int\'"; // will change
            string code1 = ad + "bipush " + numOrID.value;
            finalStack.back().code.push_back(code1);
        }
    }
    else
    {
        //serch in table
        string ad = to_string(addressCounter++) + ": ";
        finalStack.back().type = "\'int\'";                                       // will change
        string code1 = ad + "iload_" + to_string(variables[numOrID.value].first); // will change
        finalStack.back().code.push_back(code1);
        finalStack.back().value = numOrID.value;
    }
}

string ActionMaker::codeOFmulandAdd(string aa, string bb, string ccValue , string ccName, string action)
{

    if (aa == "\'int\'" && bb == "\'int\'")
    {
        if (action == "<TERM'01>")
        {
            if (ccValue == "*")
            {
                return "imul";
            }
            else if (ccValue == "/")
            {
                return "idiv";
            }
        }
        else
        {
            if (ccValue == "+")
            {
                return "iadd";
            }
            else if (ccValue == "-")
            {
                return "isub";
            }
        }
    }else if ( aa == "\'float\'" && bb == "\'float\'") {
        if (action == "<TERM'01>")
        {
            if (ccValue == "*")
            {
                return "fmul";
            }
            else if (ccValue == "/")
            {
                return "fdiv";
            }
        }
        else
        {
            if (ccValue == "+")
            {
                return "fadd";
            }
            else if (ccValue == "-")
            {
                return "fsub";
            }
        }
    }

    return "";
}