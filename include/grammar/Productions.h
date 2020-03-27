//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_PRODUCTION_H
#define STATE_MACHINE_PRODUCTION_H
#include "grammar/definitions.h"
#include "grammar/Symbol.h"
#include <map>
#include <list>

class Productions {
public:

    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<SymbolsChain, SymbolsChain>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = std::pair<const SymbolsChain&, const SymbolsChain&>;
        iterator(const iterator &other);
        iterator& operator=(const iterator &other);
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        const reference operator*();
       // const reference  operator*() const;
        //pointer operator->();
        //const pointer operator->() const;

    private:
        iterator(std::map<SymbolsChain, std::list<SymbolsChain>, Comparator>::const_iterator a,
                 std::list<SymbolsChain>::const_iterator b,
                 std::map<SymbolsChain, std::list<SymbolsChain>, Comparator>::const_iterator a_end);


        std::list<SymbolsChain>::const_iterator current_betta;
        std::map<SymbolsChain, std::list<SymbolsChain>, Comparator>::const_iterator current_alpha;
        //std::list<SymbolsChain>::iterator end_betta;
        std::map<SymbolsChain, std::list<SymbolsChain>, Comparator>::const_iterator end_alpha;
        friend class Productions;
    };

   // using const_iterator = const iterator;

    Productions();
    ~Productions();
    void addProduction(const SymbolsChain &alpha, const SymbolsChain &betta);
    bool empty() const;
    iterator begin() const;
    iterator end() const;
    //const_iterator begin() const;
   // const_iterator end() const;
   // const_iterator cbegin() const;
   // const_iterator cend() const;
    //SymbolsChain applay(SymbolsChain c);
  //  std::pair<int, int> isApplay(SymbolsChain c);
private:
   // void alphabet_check(const Symbol &s) const;
    std::map<SymbolsChain, std::list<SymbolsChain>, Comparator> productions;
};

#endif //STATE_MACHINE_PRODUCTION_H
