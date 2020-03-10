//
// Created by nrx on 09.03.2020.
//

#include "grammar/definitions.h"


bool Comparator::operator() (const SymbolsChain &a, const SymbolsChain &b) const{
    size_t sizeA = a.size();
    size_t sizeB = b.size();
    if(sizeA < sizeB) {
        return true;
    } else if(sizeA > sizeB) {
        return false;
    }

    for(auto itrA = a.begin(), itrB = b.begin();
        itrA != a.end(); itrA++, itrB++) {
        if(*itrA < *itrB) {
            return true;
        }
    }
    return false;

}