#include "../include/NFA.h"
#include <string.h>
#include <iostream>

using namespace std;

NFA::NFA() {

}

NFA::~NFA() {
}

NFA::NFA(int number, shared_ptr<Token> token) : number(number), token(token) {

}

int NFA::getNumber() {
    return number;
}

void NFA::setNumber(int number) {
    NFA::number = number;
}

shared_ptr<State> NFA::getStartState() {
    return startState;
}

void NFA::setStartState(shared_ptr<State> startState) {
    NFA::startState = startState;
}

shared_ptr<State> NFA::getEndState() {
    return endState;
}

void NFA::setEndState(shared_ptr<State> endState) {
    NFA::endState = endState;
}

list<shared_ptr<State>> NFA::getStates() {
    return states;
}

void NFA::setStates(list<shared_ptr<State>> states) {
    NFA::states = states;
}

NFA NFA::ast(NFA a1, shared_ptr<Token> token) {
    shared_ptr<Token> t1(token);
    shared_ptr<Token> t2(token);


    NFA nfa = NFA(0, token);

    shared_ptr<State> strt(new State(t1));
    shared_ptr<State> endSS(new State(t2));


    strt->setTransion(0, endSS);
    endSS->setEndState(true);
    nfa.setStartState(strt);
    nfa.setEndState(endSS);
    shared_ptr<State> a1start = a1.getStartState();
    shared_ptr<State> a1end = a1.getEndState();
    strt->setTransion(0, a1start);
    a1end->setTransion(0, endSS);
    a1end->setTransion(0, a1start);
    a1end->setEndState(false);
    return nfa;
}

NFA NFA::plusNFA(NFA a1, shared_ptr<Token> token) {
    return concat(a1, ast(a1.clone(a1), token), token);

}

NFA NFA::concat(NFA a1, NFA a2, shared_ptr<Token> token) {

    shared_ptr<State> strt(new State(token));
    shared_ptr<State> endSS(new State(token));

    NFA nfa = NFA(0, token);
    nfa.setStartState(strt);
    nfa.setEndState(endSS);
    endSS->setEndState(true);

    strt->setTransion(0, a1.getStartState());
    a1.getEndState()->setTransion(0, a2.getStartState());
    a1.getEndState()->setEndState(false);
    a2.getEndState()->setTransion(0, endSS);
    a2.getEndState()->setEndState(false);
    return nfa;
}

NFA NFA::oring(NFA a1, NFA a2, shared_ptr<Token> token) {
    NFA nfa = NFA(0, token);

    shared_ptr<Token> t1(token);
    shared_ptr<Token> t2(token);

    shared_ptr<State> strt(new State(t1));
    shared_ptr<State> endSS(new State(t2));

    strt->setTransion(0, a1.getStartState());
    strt->setTransion(0, a2.getStartState());

    shared_ptr<State> a1end = a1.getEndState();
    shared_ptr<State> a2end = a2.getEndState();
    endSS->setEndState(true);
    a1end->setEndState(false);
    a2end->setEndState(false);
    a1end->setTransion(0, endSS);
    a2end->setTransion(0, endSS);

    nfa.setStartState(strt);
    nfa.setEndState(endSS);
    return nfa;
}

NFA NFA::parcingPattern(set<shared_ptr<Token>> tokens) {
    std::set<shared_ptr<Token>>::iterator it;
    NFA nfa(0, token);
    shared_ptr<State> strt(new State(token));
    shared_ptr<State> endss(new State(token));
    endss->setEndState(false);
    nfa.setStartState(strt);
    // strt->setTransion(0,endss);
    nfa.setEndState(endss);
    for (it = tokens.begin(); it != tokens.end(); ++it) {
        shared_ptr<Token> token = *it;
        prevNFA[token->getName()] = parcingOne(token->getPattern(), token);
    }


    for (it = tokens.begin(); it != tokens.end(); ++it) {
        shared_ptr<Token> t = *it;
        NFA b = prevNFA[t->getName()];
        strt->setTransion(0, b.getStartState());
        b.getEndState()->setTransion(0, endss);
    }

    return nfa;
}

NFA NFA::parcingOne(std::string str, shared_ptr<Token> token) {
    // map prevNFA
    NFA nfa(0, token);
    shared_ptr<State> strt(new State(token));
    shared_ptr<State> endss(new State(token));
    endss->setEndState(true);
    nfa.setStartState(strt);
    strt->setTransion(0, endss);
    nfa.setEndState(endss);
    int i = 0;
    char c;
    int check = 0;
    std::string temp("");
    while (i < str.length()) {
        c = str.at(i);

        if (c == '(') {
            if (i - 1 >= 0 && str[i - 1] == '\\') {
                temp.push_back(c);

            } else {
                if (temp.length() > 0) {
                    std::map<std::string, NFA>::iterator it;
                    it = prevNFA.find(temp);
                    if (it != prevNFA.end()) {
                        nfa = concat(nfa, clone(it->second), token);
                    } else {
                        nfa = concat(nfa, charOP(temp, token), token);
                    }

                    temp = string("");
                }
                i++;
                int stackN = 1;
                std::string s("");
                c = str.at(i);
                while (stackN > 0 && i < str.length()) {

                    if (c == ')') {
                        stackN--;
                    } else if (c == '(') {
                        stackN++;
                    }
                    i++;
                    if (stackN > 0) {
                        s.push_back(c);
                    }
                    if (i < str.length()) {
                        c = str.at(i);
                    }

                }
                if (s.length() > 0) {
                    if (i < str.length() && str[i] == '*') {
                        nfa = concat(nfa, ast(parcingOne(s, token), token),
                                     token);
                    } else if (i < str.length() && str[i] == '+') {
                        nfa = concat(nfa, plusNFA(parcingOne(s, token), token),
                                     token);
                    } else {
                        i--;
                        nfa = concat(nfa, parcingOne(s, token), token);
                    }
                }
            }
        } else if (c == '|') {
            if (i + 1 < str.length()) {
                if (temp != "") {
                    std::map<std::string, NFA>::iterator it;
                    it = prevNFA.find(temp);
                    if (it != prevNFA.end()) {
                        return oring(concat(nfa, clone(it->second), token),
                                     parcingOne(str.substr(i + 1,
                                                           str.length() - 1),
                                                token), token);
                    } else {
                        return oring(concat(nfa, charOP(temp, token), token),
                                     parcingOne(str.substr(i + 1,
                                                           str.length() - 1),
                                                token), token);
                    }
                } else {
                    return oring(nfa,
                                 parcingOne(str.substr(i + 1, str.length() - 1),
                                            token), token);
                }

            } else {
                //error
            }
        } else if (i > 0 && str.at(i - 1) != 92 && c == '*') {
            std::map<std::string, NFA>::iterator it;
            it = prevNFA.find(temp);
            if (it != prevNFA.end()) {
                nfa = concat(nfa, ast(clone(it->second), token), token);
            } else {
                char cc = str.at(i - 1);
                if (temp.length() == 1) {
                    nfa = concat(nfa, ast(charOP(temp, token), token), token);
                } else {
                    string ss("");
                    ss.push_back(cc);
                    nfa = concat(nfa, concat(charOP(temp, token),
                                             ast(charOP(ss, token), token),
                                             token), token);
                }


            }
            temp = string("");
        } else if (i > 0 && str.at(i - 1) != 92 && c == '+') {
            std::map<std::string, NFA>::iterator it;
            it = prevNFA.find(temp);
            if (it != prevNFA.end()) {
                nfa = concat(nfa, plusNFA(clone(it->second), token), token);
            } else {
                char cc = str.at(i - 1);
                if (temp.length() == 1) {
                    nfa = concat(nfa, plusNFA(charOP(temp, token), token),
                                 token);
                } else {
                    string ss("");
                    ss.push_back(cc);
                    nfa = concat(nfa, concat(charOP(temp, token),
                                             plusNFA(charOP(ss, token), token),
                                             token), token);
                }


            }
            temp = string("");
        } else if (i > 0 && (i + 1 < str.length()) && (str.at(i - 1) != 92) &&
                   c == '-') {

            char b = str.at(i - 1);
            char e = str.at(i + 1);

            temp.pop_back();
            i++;
            if ((b >= 'A' && b <= 'Z' && e >= 'A' && e <= 'Z') ||
                (b >= 'a' && b <= 'z' && e >= 'a' && e <= 'z') ||
                (b >= '0' && b <= '9' && e >= '0' && e <= '9')) {

                nfa = concat(nfa, intervalOP(b, e, token), token);
            }
        } else if (c == ' ') {
            if (temp != "") {
                std::map<std::string, NFA>::iterator it;
                it = prevNFA.find(temp);
                if (it != prevNFA.end()) {
                    nfa = concat(nfa, clone(it->second), token);
                } else {
                    nfa = concat(nfa, parcingOne(temp, token), token);

                }
                temp = string("");
            }


        } else {

            temp.push_back(c);
        }

        i++;
    }

    if (temp.length() > 0) {
        std::map<std::string, NFA>::iterator it;

        it = prevNFA.find(temp);
        if (it != prevNFA.end()) {

            nfa = concat(nfa, clone(it->second), token);

        } else {

            nfa = concat(nfa, charOP(temp, token), token);

        }
    }

    return nfa;
}

NFA NFA::intervalOP(char b, char e, shared_ptr<Token> token) {
    shared_ptr<State> strt(new State(token));
    NFA nfa(0, token);
    nfa.setStartState(strt);
    int i = 0;
    shared_ptr<State> endSS(new State(token));
    endSS->setEndState(true);
    nfa.setEndState(endSS);
    char c;
    i = 0;
    c = b;
    while (c >= b && c <= e) {
        strt->setTransion(c, endSS);
        c++;
    }
    return nfa;
}

NFA NFA::charOP(std::string str, shared_ptr<Token> token) {
    shared_ptr<State> strt(new State(token));
    NFA nfa(0, token);
    nfa.setStartState(strt);
    shared_ptr<State> next(new State(token));
    char c;
    int i = 0;

    while (i < str.length()) {
        c = str.at(i);

        if (c == 92 && i + 1 < str.length()) {
            i++;
            c = str.at(i);

            if ((c >= 40 && c <= 43) || (c >= 91 && c <= 94) || c == 46 ||
                c == 63 || c == 124) {

                next = shared_ptr<State>(new State(token));
                strt->setTransion(c, next);
                strt = next;
                i++;
            } else {
                i++;
            }
        } else {
            int t = c;
            next = shared_ptr<State>(new State(token));
            strt->setTransion(c, next);
            strt = next;
            i++;
        }
    }
    strt->setEndState(true);
    nfa.setEndState(strt);

    return nfa;
}

NFA NFA::clone(NFA &nfa) {
    NFA nfaNew;
    State s = State();
    shared_ptr<State> nStart(new State(token));
    nfaNew.setStartState(nStart);
    unordered_map<shared_ptr<State>, shared_ptr<State>> mapa;
    s.clone(nfa.getStartState(), nfaNew.getStartState(), mapa);

    nfaNew.setEndState(mapa[nfa.getEndState()]);

    return nfaNew;
}
