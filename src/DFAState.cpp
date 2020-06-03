//
// Created by zeny on 3/25/20.
//


#include <bits/stdc++.h>
#include "../include/DFAState.h"

DFAState::DFAState() {

}

bool DFAState::isEndState() {
    return DFAState::endState;
}

void DFAState::setEndState(bool end) {
    DFAState::endState = end;
}

set<State> DFAState::getTransion(char input) {
    return set<State>();
}

void DFAState::setTransion(char input, shared_ptr<DFAState> e) {
    if (trans.count(input) == 0) {
        trans[input] = e;
    } else {
        cout << "error" << endl;
    }
}

void DFAState::setToken(shared_ptr<Token> t) {

}

shared_ptr<Token> DFAState::getToken() {
    return shared_ptr<Token>();
}

void DFAState::setTrans(unordered_map<char, shared_ptr<DFAState>> trans) {
    DFAState::trans = trans;
}

unordered_map<char, shared_ptr<DFAState>> DFAState::getTrans() {
    return DFAState::trans;
}

void DFAState::setSubStates(set<shared_ptr<State>> subStates) {
    DFAState::subStates.insert(subStates.begin(), subStates.end());
}

set<shared_ptr<State>> DFAState::getSubStates() {
    return subStates;
}
