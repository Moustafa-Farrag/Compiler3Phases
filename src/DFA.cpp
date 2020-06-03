#include "../include/DFA.h"
#include <bits/stdc++.h>

DFA::DFA() {
    //ctor
}

int DFA::getNumber() const {
    return number;
}

void DFA::setNumber(int number) {
    DFA::number = number;
}

const shared_ptr<State> &DFA::getStartState() const {
    return startState;
}

void DFA::setStartState(const shared_ptr<State> &startState) {
    DFA::startState = startState;
}

const shared_ptr<State> &DFA::getEndState() const {
    return endState;
}

void DFA::setEndState(const shared_ptr<State> &endState) {
    DFA::endState = endState;
}

const list<shared_ptr<State>> &DFA::getStates() const {
    return states;
}

void DFA::setStates(const list<shared_ptr<State>> &states) {
    DFA::states = states;
}







