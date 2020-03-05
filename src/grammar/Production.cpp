//
// Created by nrx on 05.03.2020.
//
#import "grammar/Production.h"
#import "grammar/Grammar.h"
#import "grammar/exception/IncorrectProduction.h"
#import <stdexcept>
#include <sstream>

Production::Production(SymbolsChain alpha, SymbolsChain betta, Grammar *g) {
    size_t  numberOfNonTerminalSymbol = 0;
    if(g == nullptr) {
        throw std::invalid_argument("Pointer of Grammar object not be nullptr");
    }
    grammar = g;
    for(auto &el : alpha) {
        alphabet_check(el);
        if(g->isNonTerminal(el)) {
            numberOfNonTerminalSymbol++;
        }

    }

    if(numberOfNonTerminalSymbol == 0) {
        throw IncorrectProduction("Symbols Chain alpha, don't containing a NonTerminal symbol");
    }

    for(auto &el : betta) {
        alphabet_check(el);
    }
    a = alpha;
    b = betta;

}

void Production::alphabet_check(const Symbol &s) const {
    if(!grammar->isTerminal(s) || !grammar->isNonTerminal(s)) {
        std::stringstream msg;
        msg << "Symbol " << s.toChar()
            <<  " is not containing in Terminal or NonTerminal alphabet";
        throw IncorrectProduction(msg.str());
    }
}

/*
SymbolsChain Production::applay(SymbolsChain c) {
    SymbolsChain result;

}


std::pair<std::pair<int, int>, bool> Production::isApplay(SymbolsChain c) {
    size_t chain_length = c.size();
    std::pair<std::pair<int, int>, bool> res;
    res.first.first = -1;
    res.first.second = -1;
    res.second = false;
    if(c.size() > a.size()) {
        return res;
    } else {
        bool done = false;
        while(!done) {
            auto itr = a.begin();
            for(; itr != a.end(); itr++) {
                if
            }
        }

    }

}*/