#include "Grammar.h"
#include "SetSymbols.h"
#include "Symbol.h"
#include <map>

class GrammBuilder {
    GrammBuilder& setTerminalSet(SetSymbols terminalSet);
    GrammBuilder& setNonTerminalSet(SetSymbols nonTerminalSet);
    GrammBuilder& setAxiom(Symbol axiom);
    GrammBuilder& addProduction(Production p);
    Gramm build();
};