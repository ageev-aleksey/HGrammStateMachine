//
// Created by nrx on 08.03.2020.
//

#include "grammar/GrammarExceptions.h"
#include "grammar/RGramarBuilder.h"
#include <iostream>
#include <sstream>


RGrammarBuilder::RGrammarBuilder() {
}

RGrammarBuilder::~RGrammarBuilder() {
    std::cout << "Destructor of RGRAMMBuilder\n";
}

RGrammarBuilder& RGrammarBuilder::setTerminals(const std::unordered_set<Symbol> &terminalSet) {
    if(grammar.nonTerminals.size() != 0) {
        for(const auto &el : terminalSet) {
            if(grammar.isNonTerminal(el)) {
                std::stringstream msg;
                msg << "Symbol " << el.toChar() << " belongs non terminal alphabet.";
                throw AlphabetError(msg.str());
            }
        }
    }
    //grammar->terminals = terminalSet;
    grammar.setTerminals(terminalSet);
    return *this;
}

RGrammarBuilder& RGrammarBuilder::setNonTerminals(const std::unordered_set<Symbol> &nonTerminalSet) {
    if(grammar.terminals.size() != 0) {
        for(const auto &el : nonTerminalSet) {
            if(grammar.isTerminal(el)) {
                std::stringstream msg;
                msg << "Symbol " << el.toChar() << " belongs non terminal alphabet.";
                throw AlphabetError(msg.str());
            }
        }
    }
    grammar.setNonTerminals(nonTerminalSet);
    return *this;
}

RGrammarBuilder& RGrammarBuilder::setAxiom(const Symbol &axiom){
    if(!grammar.isNonTerminal(axiom)) {
        std::stringstream msg;
        msg << "Symbol " << axiom.toChar() << " don't belong non terminal alphabet";
        throw AlphabetError(msg.str());
    }
    grammar.setAxiom(axiom);
    return *this;
}



void RGrammarBuilder::alphabet_check(const Symbol &s) const {
    if(!grammar.isTerminal(s) || !grammar.isNonTerminal(s)) {
        std::stringstream msg;
        msg << "Symbol " << s.toChar()
            <<  " is not containing in Terminal or NonTerminal alphabet";
        throw IncorrectProduction(msg.str());
    }
}

void RGrammarBuilder::belong_to_alphabet_check(const Symbol &s) const{
    if(grammar.isTerminal(s)) {
        std::stringstream msg;
        msg << "Symbol " << s.toChar() << " belongs non terminal alphabet.";
        throw AlphabetError(msg.str());
    }
}

RGrammarBuilder& RGrammarBuilder::setProduction(const SymbolsChain &alpha, const SymbolsChain &betta){
    size_t s = alpha.size();
    if(alpha.size() != 1) {
        std::stringstream msg;
        msg <<"Productions of right-linear grammar in left part must be containing one "
               "non terminal symbol. size of alpha: " << s;
        throw IncorrectProduction(msg.str());
    }
    if(!grammar.isNonTerminal( *alpha.begin())) {
        std::stringstream msg;
        msg << "Productions of right-linear grammar in left part must be containing non terminal symbol."
               "Alpha containing a Terminal symbol: " << alpha.begin()->toChar();
        throw IncorrectProduction(msg.str());
    }
    grammar.addProduction(alpha, betta);
    return *this;
}

Grammar RGrammarBuilder::build() {
    if (grammar.getTerminalSet().empty())
        throw BuildingException("was not set a Terminal set");
    if (grammar.getNonTerminalSet().empty())
        throw BuildingException("was not set a Non Terminal set");
    if (grammar.getAxiom().isEmptySymbol())
        throw BuildingException("was not set a Axiom symbol");
    if(grammar.productions.empty())
        throw BuildingException("was not set a productions");

    return grammar;
}
