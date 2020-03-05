//
// Created by nrx on 04.03.2020.
//
#include "grammar/Symbol.h"


Symbol::Symbol(char s) {
    symbol = s;
}

Symbol::Symbol(const Symbol &s) {
    symbol = s.symbol;
}

Symbol& Symbol::operator=(const Symbol &s) {
    symbol = s.symbol;
}

bool Symbol::operator==(const Symbol &s) const {
    return symbol == s.symbol;
}
char Symbol::toChar() const {
    return symbol;
}

std::ostream& operator<< (std::ostream &out, const Symbol &s) {
    out << s.symbol;
    return out;
}




