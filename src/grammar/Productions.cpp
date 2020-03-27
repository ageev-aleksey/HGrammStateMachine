//
// Created by nrx on 09.03.2020.
//

#include "grammar/Productions.h"
#include "grammar/GrammarExceptions.h"

Productions::Productions() = default;
Productions::~Productions() = default;

void Productions::addProduction(const SymbolsChain &alpha, const SymbolsChain &betta) {
    auto itr = productions.find(alpha);
    if(itr == productions.end()) {
        std::list<SymbolsChain> right_parts_of_production;
        right_parts_of_production.push_back(betta);
        auto res_of_insert = productions.insert(
                std::pair<SymbolsChain, std::list<SymbolsChain>>{alpha, right_parts_of_production});

        if(!res_of_insert.second) {
            throw BuildingException(std::string("error inserting"));
        }
    } else {
        itr->second.push_back(betta);
    }
}

bool Productions::empty() const {
    return productions.empty();
}

Productions::iterator Productions::begin() const {
    //return iterator(productions.begin(), productions.begin()->second.begin(), productions.end());
    return iterator(this->productions.cbegin(), this->productions.begin()->second.cbegin(), this->productions.cend());
}

Productions::iterator Productions::end() const{
    return iterator(--productions.cend(), (--productions.cend())->second.cend(), this->productions.cend());
}



Productions::iterator::iterator(std::map<SymbolsChain, std::list<SymbolsChain>, Comparator>::const_iterator a,
                                std::list<SymbolsChain>::const_iterator b,
                                std::map<SymbolsChain, std::list<SymbolsChain>, Comparator>::const_iterator end_a)
                                : current_alpha(a),  current_betta(b), end_alpha(end_a) {

}

Productions::iterator::iterator(const iterator &other) {
    *this = other;
}

const Productions::iterator::reference Productions::iterator::operator*(){
    if(current_betta == current_alpha->second.end()) {
        current_alpha++;
        current_betta = current_alpha->second.begin();
    }
    //SymbolsChain &alpha_reference = (current_alpha->first);

    return {current_alpha->first, *current_betta};
}

Productions::iterator& Productions::iterator::operator++() {
    if(current_betta == current_alpha->second.end()/*end_betta*/) {
        current_alpha++;
        current_betta = current_alpha->second.begin();
        //end_betta = current_alpha->second.end();
    } else {
        ++current_betta;
    }
    return *this;
}
Productions::iterator Productions::iterator::operator++(int) {
    iterator tmp(*this);
    ++*this;
    return tmp;
}

Productions::iterator& Productions::iterator::operator--() {
    if(current_betta == current_alpha->second.begin()) {
        --current_alpha;
        current_betta = --(current_alpha->second.end());
    } else {
        --current_betta;
    }
    return *this;
}

Productions::iterator Productions::iterator::operator--(int) {
    iterator tmp(*this);
    --*this;
    return tmp;
}

Productions::iterator& Productions::iterator::operator=(const iterator &other) {
    current_alpha = other.current_alpha;
    //current_betta = other.end_betta;
    end_alpha = other.end_alpha;
    //end_betta = other.end_betta;
}

bool Productions::iterator::operator==(const iterator &other) const {
    return current_betta == other.current_betta;
}

bool Productions::iterator::operator!=(const iterator &other) const {
   // return (current_alpha != other.current_alpha); //&& (current_betta != other.current_betta);
   return current_betta != other.current_betta;
}



