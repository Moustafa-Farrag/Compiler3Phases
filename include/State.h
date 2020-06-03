#ifndef STATE_H
#define STATE_H

#include <bits/stdc++.h>
#include "Token.h"
#include <memory>

using namespace std;


class State {
public:
    State();

    State(const shared_ptr<State> &);

    virtual ~State();

    State(shared_ptr<Token> stateToken);

    bool isEndState();

    void setEndState(bool end);

    void setTransion(char input, shared_ptr<State> e);

    void resetTransion(char input, shared_ptr<State> e);

    set<shared_ptr<State>> getTransion(char input);

    unordered_map<char, set<shared_ptr<State>>> getTrans();

    void setToken(shared_ptr<Token> t);

    shared_ptr<Token> getToken();

    void clone(shared_ptr<State> oldS, shared_ptr<State> newS,
               unordered_map<shared_ptr<State>, shared_ptr<State>> &map);

    unordered_map<char, set<shared_ptr<State>>> getAllT();

    void setEqStates(set<shared_ptr<State>> states);

    set<shared_ptr<State>> getEqStates();


protected:

private:
    unordered_map<char, set<shared_ptr<State>>> trans;
    bool endState;
    shared_ptr<Token> stateToken;
    set<shared_ptr<State>> EqStates;

};

#endif // STATE_H
