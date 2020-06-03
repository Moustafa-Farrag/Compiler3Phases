#include <bits/stdc++.h>
#include <iostream>
#include "phase2/include/FollowMaker.h"
#include "phase2/include/FirstMaker.h"
#include "phase2/include/Parser.h"
#include "phase2/include/TableBuilder.h"
#include "include/Token.h"
#include "include/State.h"
#include "include/NFA.h"
#include "include/Controller.h"
#include <memory>

using namespace std ; 

set<shared_ptr<State>> done;
set<char> allinputs;

Controller c;

void Dfs(shared_ptr<State> s) {
    unordered_map<char, set<shared_ptr<State>>> umap = s->getAllT();
    unordered_map<char, set<shared_ptr<State>>>::iterator itr;
    for (itr = umap.begin(); itr != umap.end(); itr++) {
        if (allinputs.find(itr->first) == allinputs.end()) {
            allinputs.insert(itr->first);
            c.setInput(itr->first);
        }
    }

    for (itr = umap.begin(); itr != umap.end(); itr++) {
        set<shared_ptr<State>> ss = itr->second;
        set<shared_ptr<State>>::iterator it1;
        for (it1 = ss.begin(); it1 != ss.end(); ++it1) {
            shared_ptr<State> kk = *it1;
            if (done.find(kk) != done.end()) continue;
            done.insert(kk);
            Dfs(kk);
        }
    }
}


int main() {
    shared_ptr<Token> token(new Token("or"));
    token->setPattern("a-z");
    token->setPriority(INT_MAX);
    NFA b(0, token);
    set<shared_ptr<Token>> all = c.readToken("inputForphase1.txt");
    set<shared_ptr<Token>>::iterator itr;
    for (itr = all.begin(); itr != all.end(); ++itr) {
        shared_ptr<Token> kk = *itr;
    }

    NFA a = b.parcingPattern(all);
    done.insert(a.getStartState());

    done.insert(a.getStartState());
    Dfs(a.getStartState());
    DFA d = c.nfaToDfa(a);
    done.clear();
    done.insert(d.getStartState());
    Dfs(d.getStartState());
    c.minDfa();
    cout << endl << endl << endl << endl;
    int x = 1;
    printf("state ##:  ");
    for (int i = 1; i < c.getInputs().size(); ++i) {
        printf("%10c", c.getInputs()[i]);
    }
    cout << endl;
    for (auto state : d.getStates()) {
        printf("state %2d:  %10s", x++, state->getToken()->getName().c_str());
        for (int i = 1; i < c.getInputs().size(); ++i) {
            if (state->getTransion(c.getInputs()[i]).size() > 0)
                printf("%10s", state->getTransion(
                        c.getInputs()[i]).begin()->operator->()->getToken()->getName().c_str());
            else
                printf("|--------|");
        }
        cout << endl;
    }

    done.clear();
    done.insert(d.getStartState());
    Dfs(d.getStartState());
    //cout << "num of states " << done.size() << endl;
    c.readInput("codeInput.txt", d);
    Parser p; 
    p.leftRecursion();
    p.leftFactoring() ;
    p.readGrammer("inputForphase2.txt") ;
    p.leftRecursion();
    p.leftFactoring() ;
    unordered_map<string, set<string>> pp = p.print();
    FirstMaker fm = FirstMaker(pp);
    fm.make();
    fm.printin();
    FollowMaker follow = FollowMaker( pp , fm.getF() );
    follow.setStart(p.nTerOrder[0]);
    follow.make();
    follow.print();
    TableBuilder tb = TableBuilder(fm.getF(),follow.getFollow(), pp);
    tb.build();
    tb.print();
    tb.lastInput(p.nTerOrder[0]);
    //std::cout << "this is main!" << std::endl;*/
    return 0 ;
}

    
