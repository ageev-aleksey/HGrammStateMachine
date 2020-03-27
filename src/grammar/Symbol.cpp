//
// Created by nrx on 04.03.2020.
//
#include "grammar/Symbol.h"

Symbol::Symbol() {
    symbol = EMPTY_SYMBOL;
}

Symbol::Symbol(char s) {
    set(s);
}

Symbol::Symbol(const Symbol &s) {
    symbol = s.symbol;
}

void Symbol::set(char s){
    symbol = s;
}

bool Symbol::isEmptySymbol() const {
    return symbol == EMPTY_SYMBOL;
}

bool Symbol::isOneSymbol() const {
    return symbol == ONE_SYMBOL;
}

Symbol& Symbol::operator=(const Symbol &s) {
    set(s.symbol);
}

bool Symbol::operator==(const Symbol &s) const {
    return symbol == s.symbol;
}
bool Symbol::operator!=(const Symbol &s) const {
    return symbol != s.symbol;
}
char Symbol::toChar() const {
    return symbol;
}

std::ostream& operator<< (std::ostream &out, const Symbol &s) {
    out << s.symbol;
    return out;
}

bool Symbol::operator<(const Symbol &other) const {
    return this->symbol < other.symbol;
}

