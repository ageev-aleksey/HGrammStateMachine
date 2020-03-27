#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#include "grammar/definitions.h"
#include "grammar/Productions.h"
#include "grammar/Symbol.h"
#include <list>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct GrammarStruct {
    std::unordered_set<Symbol> terminals;
    std::unordered_set<Symbol>  nonTerminals;
    std::vector<std::pair<SymbolsChain, SymbolsChain>> productions;
    Symbol axiom;
};





class Grammar {
public:


    ~Grammar();
    bool isTerminal(const Symbol &s) const;
    bool isNonTerminal(const Symbol &s) const;
    const std::unordered_set<Symbol>& getTerminalSet() const;
    const std::unordered_set<Symbol>& getNonTerminalSet() const;
    const Symbol& getAxiom() const;
    const Productions& getProductions() const;


private:
    Grammar();
    void setTerminals(const std::unordered_set<Symbol> &set);
    void setNonTerminals(const std::unordered_set<Symbol> &set);
    void setAxiom(const Symbol &s);
    void addProduction(const SymbolsChain &alpha, const SymbolsChain &betta);
    std::unordered_set<Symbol> terminals;
    std::unordered_set<Symbol>  nonTerminals;
    Symbol axiom;
    Productions productions;
    friend class RGrammarBuilder;
};


/*
namespace std {
    template<>
    struct less <Grammar::SymbolsChain> {
        explicit less() {

        }
        bool operator() (const Grammar::SymbolsChain &a, const Grammar::SymbolsChain &b) const {
            size_t sizeA = a.size();
            size_t sizeB = b.size();
            if(sizeA < sizeB) {
                return true;
            } else if(sizeA > sizeB) {
                return false;
            }

            for(auto itrA = a.begin(), itrB = b.end();
                itrA != a.end(); itrA++, itrB++) {
                if(*itrA < *itrB) {
                    return true;
                }
            }
            return false;

        }
    };
}*/

#endif