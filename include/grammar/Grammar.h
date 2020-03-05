#import "grammar/Symbol.h"
#include "grammar/SetSymbols.h"
#include "grammar/Symbol.h"
#include "grammar/Production.h"
#include "grammar/SymbolsChain.h"
#include <map>
#include <vector>

class Grammar {
public:
    class Builder {
    public:
        Builder& setTerminalSet(SetSymbols terminalSet);
        Builder& setNonTerminalSet(SetSymbols nonTerminalSet);
        Builder& setAxiom(Symbol axiom);
        Builder& createInplaceProduction(SymbolsChain alpha, SymbolsChain betta);
        Grammar build();

    private:
        Builder(Grammar *grammar);
        Grammar *g;
        friend class Grammar;
    };
    bool isTerminal(const Symbol &s) const;
    bool isNonTerminal(const Symbol &s) const;
    Builder newBuilder();

private:
    Grammar();
    SetSymbols terminals;
    SetSymbols nonTerminals;
    std::vector<Production> productions;
};