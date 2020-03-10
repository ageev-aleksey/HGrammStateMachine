//
// Created by nrx on 09.03.2020.
//

#ifndef STATE_MACHINE_DEFINITIONS_H
#define STATE_MACHINE_DEFINITIONS_H
#include "grammar/Symbol.h"
#include <list>

using SymbolsChain = std::list<Symbol>;
struct Comparator {
    bool  operator () (const SymbolsChain &a, const SymbolsChain &b) const;
};


#endif //STATE_MACHINE_DEFINITIONS_H
