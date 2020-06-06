//
// Created by zeny on 6/4/20.
//

#include "../include/ActionMaker.h"
//unordered_map<string,pair<int,string>> variables;
ActionMaker::ActionMaker()
{
    addressCounter = 0;
    varCounter = 1;
    isError = false;
}

void ActionMaker::make(string action, vector<attribute> &finalStack, string lex, stack<attribute> &s)
{

    if (action == "<PRIMITIVE_TYPE10>" || action == "<PRIMITIVE_TYPE00>")
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
    else if (action == "<STATEMENT_LIST00>" || action == "<STATEMENT_LIST'00>" || action == "<TERM00>" || action == "<SIMPLE_EXPRESSION10>" || action == "<EXPRESSION00>")
    {
        attribute aa = finalStack.back();
        for (int i = 0; i < aa.code.size(); i++)
        {
            s.top().code.push_back(aa.code[i]);
        }

        s.top().type = aa.type;
        s.top().value = aa.value;
    }
    else if (action == "<TERM'01>" || action == "<SIMPLE_EXPRESSION'01>")
    {
        // 'mulop' <TERM'00> FACTOR <TERM'01> TERM' <TERM'02>

        attribute aa = finalStack.back();
        finalStack.pop_back();

        attribute cc = finalStack.back();
        finalStack.pop_back();

        attribute bb = finalStack.back();
        finalStack.pop_back();

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

        s.top().type = aa.type;
        s.top().value = "non";
        string ad = to_string(addressCounter++) + ": " + codeOFmulandAdd(aa.type, bb.type, cc.value, cc.name, action);
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
    else if (action == "<STATEMENT_LIST01>" || action == "<STATEMENT_LIST'01>" || action == "<TERM01>" || action == "<SIMPLE_EXPRESSION11>" || action == "<EXPRESSION01>" || action == "<SIMPLE_EXPRESSION02>")
    {
        attribute temp = finalStack.back();
        finalStack.pop_back();
        //attribute relop = finalStack.back();
        //string ifInst=addIfByteCode(relop);
        finalStack.pop_back();
        for (auto i : temp.code)
            finalStack.back().code.push_back(i);
        //finalStack.back().code.push_back(ifInst);
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
        string pos;
        string typeForId;
        if (variables.find(Id.value) == variables.end())
        {
            cout << "error must be declare first" << endl;
            pos = "error";
            typeForId = "error";
            finalStack.back().code.push_back("VAR MUST BE DECLARE FIRST");
            isError = true ; 
            return;
        }
        else
        {
            pos = to_string(variables[Id.value].first);
            typeForId = variables[Id.value].second;
        }

        if (Ex.type == "float" && typeForId == "float")
        {
            string ad = to_string(addressCounter++) + ": ";
            finalStack.back().code.push_back(ad + "fstore" + "    " + pos);
        }
        else if (Ex.type == "int" && typeForId == "int")
        {
            string ad = to_string(addressCounter++) + ": ";
            finalStack.back().code.push_back(ad + "istore" + "    " + pos);
        }
        else
        {
            finalStack.back().code.push_back("NOT MATCHED TYPE");
            isError = true;
        }
        /* code */
    }
    else if (action == "<METHOD_BODY00>" || action == "<STATEMENT00>" || action == "<STATEMENT10>" || action == "<STATEMENT20>" || action == "<STATEMENT30>")
    {
        cout << "finshed........" << endl;
        attribute Assigin = finalStack.back();
        finalStack.pop_back();
        finalStack.back().code = Assigin.code;
        if (action == "<METHOD_BODY00>")
        {
            finalStack.back().code.push_back(to_string(addressCounter) + ": retrun");
        }
    }
    else if (action == "<IF04>")
    {
        finalStack.pop_back();
        finalStack.pop_back();
        attribute temp = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.back().trueList.push_back(addressCounter);
        //        string ad= to_string(addressCounter)+": ";
        //        addressCounter+=3;
        finalStack.back().code = temp.code;
        //        finalStack.back().code.push_back(ad +"if_icmplt");
    }
    else if (action == "<IF06>")
    {
        finalStack.pop_back();
        attribute st = finalStack.back();
        finalStack.pop_back();
        string goTo = to_string(addressCounter) + ": " + "goto";
        addressCounter += 3;
        finalStack.back().flaseList.push_back(addressCounter);
        string ifIns = finalStack.back().code.back() + "   " + to_string(addressCounter);
        finalStack.back().code.pop_back();
        finalStack.back().code.push_back(ifIns);
        for (auto i : st.code)
            finalStack.back().code.push_back(i);
        finalStack.back().code.push_back(goTo);
    }
    else if (action == "<EXPRESSION001>")
    {
        attribute temp = finalStack.back();
        finalStack.pop_back();
        attribute relop = finalStack.back();
        string ifInst = addIfByteCode(relop);
        finalStack.pop_back();
        for (auto i : temp.code)
            finalStack.back().code.push_back(i);
        finalStack.back().code.push_back(ifInst);
        finalStack.back().type = temp.type;
        finalStack.back().value = temp.value;
    }
    else if (action == "<IF010>")
    {
        finalStack.pop_back();
        attribute insideElse = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.pop_back();
        string gooto = finalStack.back().code.back() + "    " + to_string(addressCounter);
        finalStack.back().code.pop_back();
        finalStack.back().code.push_back(gooto);
        for (auto i : insideElse.code)
            finalStack.back().code.push_back(i);
    }
    else if (action == "<FACTOR02>")
    {
        // '(' <FACTOR00> EXPRESSION <FACTOR01> ')' <FACTOR02>
        finalStack.pop_back();
        attribute Ex = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.back().type = Ex.type;
        finalStack.back().value = Ex.value;
        finalStack.back().code = Ex.code;
    }
    else if (action == "<WHILE06>")
    {
        finalStack.pop_back();
        attribute statement = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.pop_back();
        attribute experssion = finalStack.back();
        finalStack.pop_back();
        finalStack.pop_back();
        finalStack.pop_back();
        string goto_str;
        if (experssion.code.size() > 0)
        {
            goto_str = to_string(addressCounter) + ": goto    " + address_get(experssion.code[0]);
            statement.code.push_back(goto_str);
            addressCounter += 3;
            string if_str = experssion.code.back() + "  " + to_string(addressCounter);
            experssion.code.pop_back();
            experssion.code.push_back(if_str);
            for (auto i : experssion.code)
            {
                finalStack.back().code.push_back(i);
            }
            for (auto i : statement.code)
            {
                finalStack.back().code.push_back(i);
            }
        }
        else
        {
            isError = true;
            goto_str = "THERE IS NO EXPRESSION";
            statement.code.push_back(goto_str);
            addressCounter += 3;
            for (auto i : statement.code)
            {
                finalStack.back().code.push_back(i);
            }
        }
    }
    else if (action == "<SIGN00>" || action == "<SIGN10>")
    {
        attribute sign = finalStack.back();
        finalStack.pop_back();
        finalStack.back().value = sign.value;
    }
    else if (action == "<SIMPLE_EXPRESSION01>")
    {
        attribute term = finalStack.back();
        finalStack.pop_back();
        attribute sgin = finalStack.back();
        finalStack.pop_back();
        if (sgin.value == "neg")
        {
            if (term.type == "int")
            {
                term.code.push_back(to_string(addressCounter) + ": ineg");
            }
            else if (term.type == "float")
            {
                term.code.push_back(to_string(addressCounter) + ": fneg");
            }
            addressCounter++;
        }
        finalStack.push_back(term);
        attribute aa = finalStack.back();
        for (int i = 0; i < aa.code.size(); i++)
        {
            s.top().code.push_back(aa.code[i]);
        }
        s.top().type = aa.type;
        s.top().value = aa.value;
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
    finalStack.pop_back(); //  ;
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
        if (numOrID.value.find(".") != std::string::npos)
        {
            finalStack.back().type = "float"; // will change
            string code1 = ad + "bfpush " + numOrID.value;
            finalStack.back().code.push_back(code1);
        }
        else
        {
            finalStack.back().type = "int"; // will change
            string code1 = ad + "bipush " + numOrID.value;
            finalStack.back().code.push_back(code1);
        }
    }
    else
    {
        //serch in table
        string pos;
        string typeForId;
        if (variables.find(numOrID.value) == variables.end())
        {
            cout << "error must be declare first" << endl;
            pos = "error";
            typeForId = "error";
            isError = true;
            finalStack.back().code.push_back("VAR MUST BE DECLARE FIRST");
            return;
        }
        else
        {
            pos = to_string(variables[numOrID.value].first);
            typeForId = variables[numOrID.value].second;
        }

        string ad = to_string(addressCounter++) + ": ";
        finalStack.back().type = typeForId;
        string code1;
        if (typeForId == "int")                                                // will change
            code1 = ad + "iload_" + to_string(variables[numOrID.value].first); // will change
        else if (typeForId == "float")
            code1 = ad + "fload_" + to_string(variables[numOrID.value].first);

        finalStack.back().code.push_back(code1);
        finalStack.back().value = numOrID.value;
    }
}

string ActionMaker::codeOFmulandAdd(string aa, string bb, string ccValue, string ccName, string action)
{

    if (aa == "int" && bb == "int")
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
    }
    else if (aa == "float" && bb == "float")
    {
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
    isError = true;
    return "CAN NOT DO OPERATION OT DIFFIRENT TYPE";
}

string ActionMaker::addIfByteCode(attribute relop)
{
    string result = to_string(addressCounter) + ": ";
    string value = relop.value;
    if (value.compare("<") == 0)
        result += "if_icmpge";
    else if (value.compare(">") == 0)
        result += "if_icmple";
    else if (value.compare(">=") == 0)
        result += "if_icmplt";
    else if (value.compare("<=") == 0)
        result += "if_icmpgt";
    else if (value.compare("==") == 0)
        result += "if_icmpne";
    else if (value.compare("!=") == 0)
        result += "if_icmpeq";
    addressCounter += 3;
    return result;
}

string ActionMaker::address_get(string str)
{
    string num_str = "";
    int i = 0;
    while (str[i] != ':')
    {
        num_str += str[i];
        i++;
    }
    return num_str;
}