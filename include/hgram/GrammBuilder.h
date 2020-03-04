#include "hgramm/Gramm.h"

class GrammBuilder {
    GrammBuilder& addTerminal(Terminal terminalSymbol);//Todo Terminal
    GrammBuilder& addNonTerminal(Terminal nonTerminalSymbol);//TODO NonTerminal
    GrammBuilder& setAxiom(NonTerminal axiomSymbol);//TODO NonTerminal
    GrammBuilder& addProduction(Production p)//TODO Production
    Gramm build();
};