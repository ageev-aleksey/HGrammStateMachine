//
// Created by nrx on 05.03.2020.
//

#include "grammar/Grammar.h"
#include "grammar/GrammarExceptions.h"
#include <iostream>

Grammar::Grammar() {}

Grammar::~Grammar() {
    std::cout << "Destructor of Grammar\n";
}

bool Grammar::isTerminal(const Symbol &s) const{
    return terminals.find(s) != nonTerminals.cend();
}

bool Grammar::isNonTerminal(const Symbol &s) const{
    return nonTerminals.find(s) != nonTerminals.end();
}



void Grammar::setTerminals(const std::unordered_set<Symbol> &set) {
    terminals = set;
}

void Grammar::setNonTerminals(const std::unordered_set<Symbol> &set) {
    nonTerminals = set;
}

void Grammar::setAxiom(const Symbol &s) {
    axiom = s;
}

void Grammar::addProduction(const SymbolsChain &alpha, const SymbolsChain &betta) {

}


const std::unordered_set<Symbol>& Grammar::getTerminalSet() const {
    return terminals;
}

const std::unordered_set<Symbol>& Grammar::getNonTerminalSet() const {
    return nonTerminals;
}

const Symbol& Grammar::getAxiom() const {
    return axiom;
}

/*
std::vector<std::pair<std::vector<Symbol>, std::vector<Symbol>>> Grammar::getProductions() const {
    std::vector<std::pair<std::vector<Symbol>, std::vector<Symbol>>> res;
    for(const auto &production : productions) {
        const SymbolsChain &alpha = production.first;
        for(const auto &betta : production.second) {
            std::vector<Symbol> alpha_copy, betta_copy;
            for(const Symbol &symbol : alpha) {
                alpha_copy.push_back(symbol);
            }
            for(const Symbol &symbol : betta) {
                betta_copy.push_back(symbol);
            }
            res.emplace_back(std::move(alpha_copy), std::move(betta_copy));
        }
    }
    return res;
}*/

