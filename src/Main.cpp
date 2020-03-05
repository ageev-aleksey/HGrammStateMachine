//
// Created by nrx on 04.03.2020.
//
#include "grammar/Symbol.h"
#include "grammar/SetSymbols.h"
#include "grammar/SymbolsChain.h"
#include <iostream>

template<typename T>
void print(T v) {
    for(auto &el : v) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    SetSymbols set;
    set.add(Symbol('a'));
    set.add(Symbol('b'));
    set.add(Symbol('c'));
    set.add(Symbol('a'));

    print(set);

    SymbolsChain chain;
    chain.endInsert(Symbol('a'));
    chain.endInsert(Symbol('b'));
    chain.endInsert(Symbol('c'));
    chain.endInsert(Symbol('a'));

    print(chain);

    return 0;
}
