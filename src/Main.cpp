//
// Created by nrx on 04.03.2020.
//
#include "hgram/Symbol.h"
#include "hgram/SetSymbols.h"
#include <iostream>


int main(int argc, char** argv) {
    SetSymbols set;
    set.add(Symbol('a'));
    set.add(Symbol('b'));
    set.add(Symbol('c'));
    set.add(Symbol('a'));
    for(auto& el : set) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}
