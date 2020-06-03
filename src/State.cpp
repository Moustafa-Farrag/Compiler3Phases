#include "../include/State.h"
#include "../include/Token.h"
#include <memory>

State::State() {
    //ctor
}

State::~State() {
    //dtor
}

State::State(shared_ptr<Token> stateToken) : stateToken(stateToken) {
    endState = false;
}


bool State::isEndState() {
    return endState;
}

unordered_map<char, set<shared_ptr<State>>> State::getAllT() {

    return trans;
}

void State::setTransion(char input, shared_ptr<State> e) {

    if (trans[input].find(e) == trans[input].end()) {
        trans[input].insert(e);
    }
}

void State::resetTransion(char input, shared_ptr<State> e) {
    trans.erase(input);
    if (trans[input].find(e) == trans[input].end()) {
        trans[input].insert(e);
    }
}


set<shared_ptr<State>> State::getTransion(char input) {

    if (trans.find(input) == trans.end()) {
        set<shared_ptr<State>> s;
        return s;
    }

    return trans[input];
}

void State::setEndState(bool end) {
    endState = end;
}

void State::setToken(shared_ptr<Token> t) {
    stateToken = t;
}

shared_ptr<Token> State::getToken() {

    return stateToken;
}


bool operator<(const State &left, const State &right) {
    State l = left;
    State r = right;

    return l.getToken()->getName() < r.getToken()->getName();
}

unordered_map<char, set<shared_ptr<State>>> State::getTrans() {
    return trans;
}


void State::setEqStates(set<shared_ptr<State>> states) {
    State::EqStates = states;
}

set<shared_ptr<State>> State::getEqStates() {
    return EqStates;
}

void State::clone(shared_ptr<State> oldS, shared_ptr<State> newS,
                  unordered_map<shared_ptr<State>, shared_ptr<State>> &mapS) {
    unordered_map<char, set<shared_ptr<State>>> umap = oldS->getAllT();
    if (mapS.find(oldS) == mapS.end()) {
        mapS[oldS] = newS;
    }

    unordered_map<char, set<shared_ptr<State>>>::iterator itr;

    for (itr = umap.begin(); itr != umap.end(); itr++) {

        char c = itr->first;

        set<shared_ptr<State>> setS;
        setS = itr->second;

        set<shared_ptr<State>>::iterator itS;
        for (itS = setS.begin(); itS != setS.end(); itS++) {
            shared_ptr<State> oS = *itS;
            if (mapS.find(oS) == mapS.end()) {
                shared_ptr<State> nS(new State(oS->getToken()));
                clone(oS, nS, mapS);
                newS->setTransion(c, nS);

            } else {

                newS->setTransion(c, mapS[oS]);

            }
        }

    }


    newS->setToken(oldS->getToken());
    newS->setEndState(oldS->isEndState());


}

State::State(const shared_ptr<State> &) {

}

