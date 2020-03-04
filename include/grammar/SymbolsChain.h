//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_SYMBOLSCHAIN_H
#define STATE_MACHINE_SYMBOLSCHAIN_H
#include "Symbol.h"
#include <vector>
#include <iterator>

class SymbolsChain {
public:
    SymbolsChain();
    SymbolsChain(const SymbolsChain &sc);
    SymbolsChain(SymbolsChain &&sc);

    SymbolsChain& addInEnd(Symbol s);
    SymbolsChain& add()
    SymbolsChain& remove(Symbol s);

class iterator {
    using difference_type = size_t;
    using value_type  = Symbol;
    using pointer = *Symbol;
    using reference = &Symbol;
    using iterato_category = std::bidirectional_iterator_tag;
    iterator (std::list<Symbol>::iterator);

};


private:
    std::list<Symbol> chain;
};

#endif //STATE_MACHINE_SYMBOLSCHAIN_H
