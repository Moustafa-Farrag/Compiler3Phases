#include "../include/Token.h"

Token::Token() {
    //ctor
}

Token::~Token() {
    //dtor
}


Token::Token(string name) : name(name) {}

Token::Token(string name, string pattern, int priority) : name(name),
                                                          pattern(pattern),
                                                          priority(priority) {}


string Token::getName() {
    return name;
}

void Token::setName(string name) {
    Token::name = name;
}

string Token::getPattern() {
    return pattern;
}

void Token::setPattern(string pattern) {
    Token::pattern = pattern;
}

int Token::getPriority() {
    return priority;
}

void Token::setPriority(int priority) {
    Token::priority = priority;
}

