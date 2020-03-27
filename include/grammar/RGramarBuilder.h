#ifndef _RGRAMMAR_BUILDER_H_
#define _RGRAMMAR_BUILDER_H_

#include "grammar/Grammar.h"


class RGrammarBuilder {
public:
    RGrammarBuilder();
    ~RGrammarBuilder();
    RGrammarBuilder& setTerminals(const std::unordered_set<Symbol> &terminalSet);
    RGrammarBuilder& setNonTerminals(const std::unordered_set<Symbol> &nonTerminalSet);
    RGrammarBuilder& setAxiom(const Symbol &axiom);
    RGrammarBuilder& setProduction(const SymbolsChain &alpha, const SymbolsChain &betta);
    Grammar build();
    Grammar build(GrammarStruct gs);
private:
    void alphabet_check(const Symbol &s) const;
    void belong_to_alphabet_check(const Symbol &s) const;
    Grammar grammar;
};

#endif