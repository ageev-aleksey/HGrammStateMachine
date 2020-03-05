//
// Created by nrx on 05.03.2020.
//

#include "grammar/Grammar.h"

Grammar::Builder Grammar::newBuilder() {
    return Builder(new Grammar());
}


bool Grammar::isTerminal(const Symbol &s) const{
    return terminals.contain(s);
}

bool Grammar::isNonTerminal(const Symbol &s) const{
    return nonTerminals.contain(s);
}



