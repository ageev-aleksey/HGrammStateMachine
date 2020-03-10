//
// Created by nrx on 05.03.2020.
//
/*
#include <unordered_map>
#include "grammar/SymbolsChain.h"



SymbolsChain::SymbolsChain() : _size(0) {}

SymbolsChain::SymbolsChain(const SymbolsChain &s) {
    chain = s.chain;
    _size = s._size;
}

SymbolsChain::SymbolsChain(SymbolsChain &&s) {
    chain = move(s.chain);
    _size = s._size;
    s._size = 0;
}

SymbolsChain& SymbolsChain::endInsert(const Symbol &s) {
    chain.push_back(s);
    _size++;
}

SymbolsChain& SymbolsChain::insert(const iterator &pos,const Symbol &s) {
    chain.insert(pos.itr, s);
    _size++;
}

SymbolsChain& SymbolsChain::remove(const iterator &pos) {
    chain.erase(pos.itr);
    _size--;
}
size_t SymbolsChain::size() {
    return  _size;
}

SymbolsChain::iterator SymbolsChain::begin() {
    return iterator(chain.begin());
}

SymbolsChain::iterator SymbolsChain::end() {
    return iterator(chain.end());
}

SymbolsChain::iterator::iterator(std::list<Symbol>::iterator itr) {
    this->itr = itr;
}

SymbolsChain::iterator& SymbolsChain::iterator::operator++() {
    ++itr;
    return *this;
}

SymbolsChain::iterator SymbolsChain::iterator::operator++(int) {
    iterator tmp(itr);
    ++itr;
    return tmp;
}

SymbolsChain::iterator& SymbolsChain::iterator::operator--() {
    --itr;
    return *this;
}

SymbolsChain::iterator SymbolsChain::iterator::operator--(int) {
    iterator tmp(itr);
    --itr;
    return tmp;
}

SymbolsChain::iterator& SymbolsChain::iterator::operator=(const iterator &other) {
    this->itr = other.itr;
}

bool SymbolsChain::iterator::operator==(const iterator &other) const {
    return this->itr == other.itr;
}

bool SymbolsChain::iterator::operator!=(const iterator &other) const {
    return this->itr != other.itr;
}

SymbolsChain::iterator::pointer SymbolsChain::iterator::operator->(){
    return itr.operator->();
}

SymbolsChain::iterator::reference SymbolsChain::iterator::operator*(){
    return itr.operator*();
}

SymbolsChain::iterator SymbolsChain::findSubChain(SymbolsChain &s) {
    size_t len = s.size();
    if(len == 0)
        return end();
    else if(len == 1) {
        auto sItr = s.begin();
        for( auto itr = chain.begin(); itr != chain.end(); itr++) {
            if(*itr == *sItr) {
                return SymbolsChain::iterator(itr);
            }
        }
    } else {
        std::unordered_map<Symbol, size_t> offsetTable;
        size_t step = 1;
        for(auto itr= (s.end()--)--; itr != s.begin(); itr--) {
            offsetTable.insert({*itr, step});
            step++;
        }
        auto endElement = offsetTable.find(*(s.end()--));
        if (endElement == offsetTable.end()) {
            offsetTable.insert({*(s.end()--), len});
        }

    }

}

SymbolsChain &SymbolsChain::operator=(const SymbolsChain &other) = default;
*/