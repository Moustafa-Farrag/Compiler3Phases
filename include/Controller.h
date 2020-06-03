//
// Created by zeny on 3/24/20.
//

#ifndef COMPILER_CONTROLLER_H
#define COMPILER_CONTROLLER_H

#include "NFA.h"
#include "Token.h"
#include "DFA.h"
#include "DFAState.h"
#include <bits/stdc++.h>

class Controller {
private:
    vector<shared_ptr<Token>> tokens;
    vector<NFA> A;
    vector<char> inputs;
    NFA N;
    DFA D;

    //  set<struct shared_ptr<State>> epsClosure(shared_ptr<State> s, char input);

    //  set<shared_ptr<State>> epsClosure(set<shared_ptr<State>> s, char input);

    //  shared_ptr<State> getUnMarked(unordered_map<set<shared_ptr<State>>, bool> &DStates);

    bool equalStates(vector<vector<shared_ptr<State>>> p, shared_ptr<State> s1,
                     shared_ptr<State> s2);

    vector<vector<shared_ptr<State>>>
    smash(vector<vector<shared_ptr<State>>> p);

    vector<vector<shared_ptr<State>>> split(vector<shared_ptr<State>> s);

    bool areEqual(vector<vector<shared_ptr<State>>> p, shared_ptr<State> s1,
                  shared_ptr<State> s2, char in);

    bool inSameVector(vector<vector<shared_ptr<State>>> p, shared_ptr<State> t1,
                      shared_ptr<State> t2);

    bool statesExistInVector(vector<shared_ptr<State>> p, shared_ptr<State> t1,
                             shared_ptr<State> t2);

    bool containSamePartitions(vector<vector<shared_ptr<State>>> v1,
                               vector<vector<shared_ptr<State>>> v2);

    void reflectMinimizedDfa(vector<vector<shared_ptr<State>>> partitions);

    void mushTwoStates(shared_ptr<State> state, shared_ptr<State> state1);

    void setNewStates(const vector<vector<shared_ptr<State>>> &partitions);


public:
    Controller();

    virtual ~Controller();

    const vector<shared_ptr<Token>> &getTokens() const;

    void setTokens(const vector<shared_ptr<Token>> &tokens);

    const vector<NFA> &getA() const;

    void setA(const vector<NFA> &a);

    const NFA &getN() const;

    void setN(const NFA &n);

    const DFA &getD() const;

    void setD(const DFA &d);

    set<shared_ptr<Token>> readToken(string path);

    shared_ptr<Token>
    preProcess(vector<shared_ptr<Token>> tokens, int tokenNum);

    DFA nfaToDfa(NFA A);

    bool checkD(set<shared_ptr<State>> set);

    NFA oringAll(vector<NFA> A);

    void minDfa();

    void getAllInputs(DFA A);

    set<shared_ptr<State>> epsClosure(shared_ptr<State> state);

    shared_ptr<State> setup(set<shared_ptr<State>> states);

    set<shared_ptr<State>> moveTo(set<shared_ptr<State>> states, char input);

    set<shared_ptr<State>> moveTo(shared_ptr<State> state, char input);

    set<shared_ptr<State>> epsClosure(set<shared_ptr<State>> states);

    bool checkD(list<shared_ptr<State>> list, shared_ptr<State> state,
                shared_ptr<State> *clone);

    vector<char> getInputs();

    void setInput(char input);

    static bool ifEndStatesTheyDontHaveSameToken(shared_ptr<State> &sharedPtr,
                                                 shared_ptr<State> &sharedPtr1);

    std::string inputToken(std::string input, DFA dfa);

    void readInput(std::string path, DFA dfa);
};


#endif //COMPILER_CONTROLLER_H
