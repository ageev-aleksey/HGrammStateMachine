//
// Created by nrx on 04.03.2020.
//

#ifndef STATE_MACHINE_SYMBOLSCHAIN_H
#define STATE_MACHINE_SYMBOLSCHAIN_H
#include "grammar/Symbol.h"
#include <list>
#include <iterator>



class SymbolsChain {
public:
    class iterator {
    public:
        friend class SymbolsChain;

        using difference_type = size_t;
        using value_type  = Symbol;
        using pointer = Symbol *;
        using reference = Symbol &;
        using iterato_category = std::bidirectional_iterator_tag;

        iterator(std::list<Symbol>::iterator itr);
        iterator& operator=(const iterator &other);
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
        pointer operator->();
        reference operator*();
        const reference operator*();
        value_type get();
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);

    private:
        std::list<Symbol>::iterator itr;
    };
    //TODO CONST ITERATOR
    /*class const_iterator {
    public:
        friend class SymbolsChain;

        using difference_type = size_t;
        using value_type  = Symbol;
        using pointer = Symbol *;
        using reference = Symbol &;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator(std::list<Symbol>::iterator itr);
        iterator& operator=(const iterator &other);
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
        const pointer operator->();
        const reference operator*();
        const reference operator*();
        value_type get();
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);

    private:
        std::list<Symbol>::iterator itr;
    };*/
    SymbolsChain();
    SymbolsChain(const SymbolsChain &sc);
    SymbolsChain(SymbolsChain &&sc);
    SymbolsChain& operator=(const SymbolsChain &other);
    size_t size();
    SymbolsChain& endInsert(const Symbol &s);
    SymbolsChain& insert(const iterator &pos,const Symbol &s);
    SymbolsChain& remove(const iterator &pos);
    iterator findSubChain(SymbolsChain &s);//TODO set argument const when will created Const iterator
    iterator begin();
    iterator end();
    /*const iterator begin() const;
    const iterator end() const;*/

private:
    std::list<Symbol> chain;
    size_t _size;
};




#endif //STATE_MACHINE_SYMBOLSCHAIN_H
