//
// Created by nrx on 13.03.2020.
//

#include "grammar/Alg.h"
#include "Matrix.h"

std::pair<Matrix<SymbolsChain>, std::unordered_map<Symbol, size_t>> Alg::createStandardSystemEquation(const Grammar &g) {
        size_t num_equals = g.getNonTerminalSet().size();
        Matrix<SymbolsChain> res(num_equals, num_equals+1);
        for(size_t i = 0; i < res.getNrow(); i++) {
            for(size_t j= 0;j < res.getNcol(); j++) {
                res.at(i, j).push_back(Symbol::EMPTY_SYMBOL);
            }
        }
        std::unordered_map<Symbol, size_t> symbol_to_index;
        size_t last_index = 0;
        for(const auto &el : g.getNonTerminalSet()) {
            symbol_to_index.insert(std::pair<Symbol, size_t>(el, last_index));
            ++last_index;
        }

        Symbol right = *(*g.getProductions().begin()).first.begin();
        int j = symbol_to_index.at(right);
        for(const auto& prod : g.getProductions()) {
            if(right != *prod.first.begin()) {
                right = *prod.first.begin();
                j = symbol_to_index.at(right);
            }
            const Symbol &s = *(--prod.second.end());
            if(g.isNonTerminal(s)) {
                size_t i = symbol_to_index.at(s);
                SymbolsChain tmp(prod.second.begin(), --prod.second.end());
                res.at(j, i) = std::move(tmp);
            } else {
                for(const auto &symbol : prod.second) {
                    res.at(j, last_index).push_back(symbol);
                }
                if(prod.second.empty()) {
                    res.at(j, last_index).emplace_back(Symbol::EMPTY_SYMBOL);
                }

            }

        }
    return std::pair<Matrix<SymbolsChain>, std::unordered_map<Symbol, size_t>>(res, symbol_to_index);


}

void symbols_append(Matrix<std::string> &m, const SymbolsChain ch, size_t r, size_t c) {
    for(const auto &el : ch) {
        m.at(r, c).push_back(el.toChar());
    }
}

Matrix<std::string> Alg::solveStandardSystemEquation(const Matrix<SymbolsChain> &m) {
    size_t ncol = m.getNcol();
    size_t nrow = m.getNrow();
    Matrix<std::string> mt(ncol, nrow);
    for(size_t i = 0; i < nrow; ++i){
        for(size_t k = i+1; k < nrow; ++k) {
            for(size_t t = i+1; t < ncol; ++t ) {
                symbols_append(mt, m.at(k, i), k, t);
                mt.at(k, t).push_back('(');
                symbols_append(mt, m.at(i, i), k, t);
                mt.at(k, t).push_back(')');
                mt.at(k, t).push_back('*');
                symbols_append(mt, m.at(i, t), k, t);
                mt.at(k, t).push_back('+');
                symbols_append(mt, m.at(k, t), k, t);
            }
        }
    }
    return mt;

}