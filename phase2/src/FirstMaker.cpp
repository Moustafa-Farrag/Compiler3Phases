//
// Created by zeny on 4/12/20.
//

#include "../include/FirstMaker.h"

FirstMaker::FirstMaker(unordered_map<string, set<string>> &productions) : Productions(productions) {
    calcLanguage();
}

const unordered_map<string,set<string>>  &FirstMaker::getF() const {
    return F;
}

void FirstMaker::setF(const unordered_map<string,set<string>>  &f) {
    F = f;
}

const set<string> &FirstMaker::getLanguage() const {
    return language;
}

void FirstMaker::setLanguage(const set<string> &language) {
    FirstMaker::language = language;
}

void FirstMaker::calcLanguage() {
    for( const auto& production:this->Productions){
        language.insert(production.first);
        for( const auto& product:production.second){
            language.insert(product);
            vector<string>words=tokenize(product);
            for(const auto& word : words){
                language.insert(word);
            }
        }
    }
}

bool FirstMaker::isTerminal(string s) {
    return (s[0]=='\''&&s[s.size()-1]=='\''&&s.find(' ')==string::npos);
}

void FirstMaker::make() {
    unordered_map<string,set<string>> first;
    unordered_map<string,set<string>> dummyFirst;

    for(auto l:language){
        set<string> set={};
        if(isTerminal(l)||(tokenize(l).size()==1&&isTerminal(l))||l=="eeee"){
            set.insert(l);
            first[l]=set;
        }else if(!isTerminal(l)&&l!="eeee"){
            first[l]=set;
        }
    }

    do{
        dummyFirst=first;
        for(auto production:this->Productions){
            for(auto product: production.second){
                vector<string>words=tokenize(product);
                set<string> currentFirst;
                int wordCount=0, k=words.size()-1;
                for(auto w:first[words[0]]){
                    if(w!="eeee")
                        currentFirst.insert(w);
                }
                while(first[words[wordCount]].find("eeee") != first[words[wordCount]].end()&&wordCount<words.size()-1){
                    wordCount++;
                    for(auto w:first[words[wordCount]]){
                        if(w!="eeee")
                            currentFirst.insert(w);
                    }
                }

                if(wordCount==k&&first[words[k]].find("eeee") != first[words[k]].end())
                    currentFirst.insert("eeee");
                first[product].insert(currentFirst.begin(),currentFirst.end());
                first[production.first].insert(currentFirst.begin(),currentFirst.end());
            }
        }
    }while(first!=dummyFirst);
    setF(first);
}

vector<string> FirstMaker::tokenize(string s) {
    // Vector of string to save tokens
    vector <string> tokens;

    // stringstream class check1
    stringstream check1(s);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

void FirstMaker::printin() {

    cout << "-----------------------------"  << endl ; 
    for(auto umap : this->getF()) {
        cout << umap.first << ":   " ;
        for(auto s:umap.second){
            cout << s << "  " ;
        }
        cout << endl ; 
    }
}
