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
    //SymbolsChain applay(SymbolsChain c);
  //  std::pair<int, int> isApplay(SymbolsChain c);
private:
    void alphabet_check(const Symbol &s) const;
    SymbolsChain a;
    SymbolsChain b;
};

#endif //STATE_MACHINE_PRODUCTION_H
