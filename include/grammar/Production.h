//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_PRODUCTION_H
#define STATE_MACHINE_PRODUCTION_H
#include "Grammar.h"
#include "SymbolsChain.h"

class Production {
public:
    Production(SymbolsChain a, SymbolsChain b, Grammar *g);
    ~Production();
    SymbolsChain applay(SymbolsChain c);
private:
    Gramm *grammar;
    SymbolsChain a;
    SymbolsChain b;
};

#endif //STATE_MACHINE_PRODUCTION_H
