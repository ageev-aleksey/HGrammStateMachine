//
// Created by nrx on 13.03.2020.
//

#ifndef STATE_MACHINE_ALG_H
#define STATE_MACHINE_ALG_H
#include "grammar/definitions.h"
#include "grammar/Grammar.h"
#include "Matrix.h"


class Alg {
public:
    static Matrix<std::string> solveStandardSystemEquation(const Matrix<SymbolsChain> &m);
    static std::pair<Matrix<SymbolsChain>, std::unordered_map<Symbol, size_t>> createStandardSystemEquation(const Grammar &g);

};


#endif //STATE_MACHINE_ALG_H
