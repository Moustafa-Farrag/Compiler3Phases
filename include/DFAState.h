//
// Created by zeny on 3/25/20.
//

#ifndef COMPILER2_DFASTATE_H
#define COMPILER2_DFASTATE_H

#include "State.h"
#include "Token.h"
#include <bits/stdc++.h>

class DFAState {

public:
    DFAState();

    bool isEndState();

    void setEndState(bool end);

    void setTransion(char input, shared_ptr<DFAState> e);

    set<State> getTransion(char input);

    void setToken(shared_ptr<Token> t);

    shared_ptr<Token> getToken();

    unordered_map<char, shared_ptr<DFAState>> getTrans();

    void setTrans(unordered_map<char, shared_ptr<DFAState>> trans);

    void setSubStates(set<shared_ptr<State>> subStates);

    set<shared_ptr<State>> getSubStates();

private:
    unordered_map<char, shared_ptr<DFAState>> trans;
    set<shared_ptr<State>> subStates;
    bool endState;
    shared_ptr<Token> stateToken;
};

#endif //COMPILER2_DFASTATE_H
