//
// Created by nrx on 04.03.2020.
//
#include "hgram/SetSymbols.h"

SetSymbols::iterator::iterator(std::unordered_set<Symbol, Symbol::hash>::iterator itr) {
    this->itr = itr;
}

SetSymbols::iterator& SetSymbols::iterator::operator=(const iterator &itr) {
    this->itr = itr.itr;
    return *this;
}

SetSymbols::iterator::iterator(const iterator &itr) {
    this->itr = itr.itr;
}

SetSymbols::iterator& SetSymbols::iterator::operator++() {
    ++itr;
    return *this;
}

SetSymbols::iterator SetSymbols::iterator::operator++(int) {
    iterator tmp(*this);
    ++itr;
    return tmp;
}

const Symbol SetSymbols::iterator::operator*() {
    return *itr;
}

bool SetSymbols::iterator::operator==(const iterator &other) {
    return this->itr == other.itr;
}

bool SetSymbols::iterator::operator!=(const iterator &other) {
    return this->itr != other.itr;
}

SetSymbols::SetSymbols() {

}

SetSymbols::SetSymbols(const SetSymbols& set) {
    this->set = set.set;
}

SetSymbols::SetSymbols(SetSymbols &&set) {
    this->set = std::move(set.set);
}

void SetSymbols::add(const Symbol &s) {
    set.insert(s);
}

void SetSymbols::remove(const Symbol &s) {
    set.erase(s);
}

bool SetSymbols::contain(const Symbol &s) const {
    return set.find(s) != set.cend();
}

SetSymbols::iterator SetSymbols::begin() {
    return iterator(set.begin());
}

SetSymbols::iterator SetSymbols::end() {
    return iterator(set.end());
}