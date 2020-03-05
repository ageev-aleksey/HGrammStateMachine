#include "grammar/Grammar.h"
#include "grammar/SetSymbols.h"
#include "grammar/Symbol.h"
#include "grammar/Production.h"
#include <map>

class GrammarBuilder {
public:
    GrammBuilder& setTerminalSet(SetSymbols terminalSet);
    GrammBuilder& setNonTerminalSet(SetSymbols nonTerminalSet);
    GrammBuilder& setAxiom(Symbol axiom);
    GrammBuilder& createInplaceProduction(SymbolsChain alpha, SymbolsChain betta);
    Grammar build();
private:
    GrammarBuilder();
};