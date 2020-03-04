//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_SETSYMBOLS_H
#define STATE_MACHINE_SETSYMBOLS_H
#include <unordered_set>
#include <iterator>
#include "Symbol.h"

class SetSymbols {
public:
class iterator : public std::iterator<std::forward_iterator_tag,
                                      Symbol,Symbol,const Symbol*,
                                      Symbol>
    {
    public:
        explicit iterator(std::unordered_set<Symbol, Symbol::hash>::iterator itr);
        iterator(const iterator &i);
        iterator& operator=(const iterator& itr);
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& itr);
        bool operator!=(const iterator& itr);
        const Symbol operator*();
    private:
    std::unordered_set<Symbol, Symbol::hash>::iterator itr;

    };
    SetSymbols();
    SetSymbols(const SetSymbols& set);
    SetSymbols(SetSymbols &&set);
    iterator begin();
    iterator end();
    void add(const Symbol &s);
    void remove(const Symbol &s);
    bool contain(const Symbol &s) const;
private:
    std::unordered_set<Symbol, Symbol::hash> set;
};


#endif //STATE_MACHINE_SETSYMBOLS_H
