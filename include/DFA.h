//
// Created by zeny on 3/24/20.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H


#include "State.h"
#include "DFAState.h"
#include <bits/stdc++.h>

class DFA {
private:
    int number; // we may remove that
    shared_ptr<State> startState;
    shared_ptr<State> endState;
    list<shared_ptr<State>> states;
public:
    DFA();

    int getNumber() const;

    void setNumber(int number);

    const shared_ptr<State> &getStartState() const;

    void setStartState(const shared_ptr<State> &startState);

    const shared_ptr<State> &getEndState() const;

    void setEndState(const shared_ptr<State> &endState);

    const list<shared_ptr<State>> &getStates() const;

    void setStates(const list<shared_ptr<State>> &states);

};


#endif //COMPILER_DFA_H
