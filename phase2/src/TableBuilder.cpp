//
// Created by zeny on 4/15/20.
//

#include "../include/TableBuilder.h"
#include <utility>

TableBuilder::TableBuilder(unordered_map<string, set<string>> first, unordered_map<string, set<string>> follow,
                           unordered_map<string, set<string>> productions)
    : first(first), follow(follow), productions(productions)
{

    calcTerminals();
}

void TableBuilder::build()
{
    map<pair<string, string>, string> t = {};
    for (auto production : this->productions)
    {
        for (auto terminal : this->terminals)
        {
            t[{production.first, terminal}] = "error";
        }
        int c1 = 0 ;
        for (auto product : production.second)
        {
            vector <string> spilted = tokenize(product);
            string temp = "" ;  
            for ( int j = 0 ; j < spilted.size() ; j++ ){

                temp += spilted[j] + " <"  + production.first + to_string(c1) +  to_string(j) + "> " ;   
            }
            for (auto terminal : this->terminals)
            {
                bool thisSlotIsTaken = false;
                if (this->first[product].find(terminal) != this->first[product].end())
                {
                    t[{production.first, terminal}] = temp;
                    thisSlotIsTaken = true;
                }
                if (this->follow[production.first].find(terminal) != this->follow[production.first].end())
                { //se if it can be [product]
                    if (this->first[production.first].find("eeee") != this->first[production.first].end())
                    {
                        if (this->productions[production.first].find("eeee") != this->productions[production.first].end() &&
                            thisSlotIsTaken)
                        {
                            errorMes.push_back("multiple productions in one slot error !!");
                            break;
                        }
                        t[{production.first, terminal}] = "eeee";
                    }
                    else if (t[{production.first, terminal}] == "error")
                    {
                        t[{production.first, terminal}] = "synch";
                    }
                }
            }
            c1++ ; 
        }
    }
    this->table = t;
}

void TableBuilder::calcTerminals()
{
    set<string> s;
    for (const auto &production : this->productions)
    {
        for (const auto &product : production.second)
        {
            vector<string> words = tokenize(product);
            for (const auto &word : words)
            {
                if (isTerminal(word))
                {
                    s.insert(word);
                }
            }
        }
    }
    s.insert("\'$\'");
    this->terminals = s;
}

vector<string> TableBuilder::tokenize(string s)
{
    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(s);

    string intermediate;
    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool TableBuilder::isTerminal(string s)
{
    return (s[0] == '\'' && s[s.size() - 1] == '\'' && s.find(' ') == string::npos);
}
/*
bool TableBuilder::isTerminal(string s) {
    return (s[0]=='\''&&s[s.size()-1]=='\''&&s.find(' ')==string::npos);
}
*/
void TableBuilder::lastInput(string firstNon)
{

    vector<string> inputWords;
    vector<string> lexs;

    // reading input
    fstream file;
    string word, lex, dash, t, q, filename;
    filename = "outputForPhase1.txt";
    file.open(filename.c_str());

    while (file >> word >> dash >> lex)
    {
        word = "\'" + word + "\'";
        inputWords.push_back(word);
        lexs.push_back(lex);
    }

    // ----------
    stack<attribute> s;
    attribute a; 
    a.name = "\'$\'" ; 
    s.push(a);
    attribute ia; 
    ia.name = firstNon; 
    s.push(ia);
    inputWords.push_back("\'$\'");
    int i = 0;
    if (!errorMes.size())
    {
        while (!s.empty() && i < inputWords.size())
        {
            attribute stackP = s.top();
            s.pop();
            //  cout << "ssss "  << stackP << " " << i << " " << inputWords[i] << endl ;
            if (stackP.name == "synch")
            {

                PrintingInOut(i, s, errorMes, inputWords, stackP);
                errorMes.push_back("error synch\n");
                continue;
            }

            if (stackP.name == "eeee")
            {
                continue;
            }

            if (stackP.name[0] == '<' && stackP.name.size() > 2 ){
                cout << stackP.name << endl ; 
                continue ;
            }
            if (!isTerminal(stackP.name))
            {
                // may the string from table must spilt

                PrintingInOut(i, s, errorMes, inputWords, stackP);
                if (table[{stackP.name, inputWords[i]}] != "")
                {
                    vector<string> ss = tokenize(table[{stackP.name, inputWords[i]}]);
                    for (int j = ss.size() - 1; j >= 0; j--)
                    {
                        if (ss[j] != " " && ss[j] != ""){
                            attribute b ; 
                            b.name = ss[j] ; 
                            s.push(b);
                         }
                    }
                }
                else
                {
                    //PrintingInOut(  i , s, errorMes,inputWords, stackP);
                    errorMes.push_back("error in table\n");
                    errorMes.push_back(stackP.name + " " + inputWords[i]);
                    break;
                    //cout << "Www " << stackP << " ff " << inputWords[i] << endl ;
                }

                // handel error of not found , i can handel it alone as prev but of good message i prefer not
                if (s.top().name == "error")
                {

                    PrintingInOut(i, s, errorMes, inputWords, stackP);
                    errorMes.push_back(stackP.name + "Error:(illegal " + stackP.name + ") discard " + inputWords[i] + "\n");
                    s.pop();
                    s.push(stackP);
                    i++;
                }
                else
                {
                    errorMes.push_back(stackP.name + " to " + table[{stackP.name, inputWords[i]}] + "\n");
                }
                continue;
            }

            // here is  terminal
            //  stackP.substr( 1 , stackP.size() -1  ) ; // tryig to remove ' '

            if (stackP.name != inputWords[i])
            {

                PrintingInOut(i, s, errorMes, inputWords, stackP);
                errorMes.push_back(stackP.name + " Error: missing " + inputWords[i] + ", inserted \n");
                continue;
            }

            // they are similar
            PrintingInOut(i, s, errorMes, inputWords, stackP);
            errorMes.push_back("match " + stackP.name + "\n");
            i++;
        }

        if (s.empty() && i == inputWords.size())
        {
            errorMes.push_back("done\n");
        }
        else
        {
            errorMes.push_back("not matched input\n");
        }
    }

    ofstream MyFile("outputForphase2.txt");
    int c = 0;

    for (string s : errorMes)
    {
        MyFile << s;
        c++;
        if (c % 3 == 0)
            MyFile << "-------------------" << endl;
    }

    MyFile.close();

    ofstream MyFile2("outputForphase2Justmes.txt");
    for (int k = 2; k < errorMes.size(); k += 3)
    {
        MyFile2 << errorMes[k] << endl;
    }
    // Close the file
    MyFile2.close();
}

void TableBuilder::print()
{
    cout << endl
         << "------table--------" << endl;
    for (auto t : this->table)
    {
        cout << t.first.first << " ," << t.first.second << " :";
        cout << t.second << endl;
    }
}

void TableBuilder::PrintingInOut(int i, stack<attribute> &s, vector<string> &errorMes, vector<string> &inputWords, attribute stackP)
{

    stack<attribute> temp = s;
    vector<attribute> temp2;
    string my_stack = "";
    while (!temp.empty())
    {
        temp2.push_back(temp.top());
        temp.pop();
    }
    for (int k = temp2.size() - 1; k >= 0; k--)
        my_stack += temp2[k].name + " ";
    my_stack += stackP.name + "\n";
    errorMes.push_back(my_stack);
    string my_input = "";
    for (int k = inputWords.size() - 1; k >= i; k--)
        my_input += inputWords[k] + " ";
    my_input += "\n";
    errorMes.push_back(my_input);
    // errorMes.push_back(stackP + "Error:(illegal " + stackP + ") discard " + inputWords[i] + "\n");
}
