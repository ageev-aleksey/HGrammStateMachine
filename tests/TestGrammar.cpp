//
// Created by nrx on 13.03.2020.
//
#include "gtest/gtest.h"
#include "grammar/Grammar.h"
#include "grammar/RGramarBuilder.h"
#include "grammar/GrammarExceptions.h"
#include <iostream>
#include <type_traits>

template<typename Iterable>
void print(Iterable v) {
    print(v, typename std::iterator_traits<decltype(v.begin())>::value_type());
}

template<typename Iterable, typename vt>
void print(Iterable v, vt) {
    for(const auto &el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

template<typename Iterable>
void print(Iterable v, std::pair<SymbolsChain , SymbolsChain>) {
    for(const auto &el : v) {
        std::cout << "(";
        for(const auto &s : el.first) {
            std::cout << s;
        }
        std::cout << "; ";
        for(const auto &s : el.second) {
            std::cout << s;
        }
        std::cout << ")";
    }
    std::cout << std::endl;
}

TEST(GrammarTest, CreateGrammar) {
    Grammar g =  RGrammarBuilder().build({
        {'0', '1'},
        {'S', 'A', 'B'},
        {
                {
                        {'S'},
                        {'0', 'A'}
                },
                {
                        {'S'},
                        {'1', 'S'}
                },
                {
                        {'S'},
                        {'1'}
                },
                {
                        {'A'},
                        {'0', 'B'}
                },
                {
                        {'A'},
                        {'1', 'A'}
                },
                {
                        {'B'},
                        {'0', 'S'}
                },
                {
                        {'B'},
                        {'1', 'B'}
                },

        },
        {'S'}
    });

    print(g.getTerminalSet());
    print(g.getNonTerminalSet());
    print(g.getProductions());
}

TEST(GrammarTest, ThorwOnTryCreateNonRightLinearGramar) {
    ASSERT_THROW(RGrammarBuilder().build({
        {'a', 'b', 'c'},
        {'S', 'T'},
        {
            {
                {'S'},
                {'T', 'a'}
            },
            {
                {'T'},
                {'a', 'b', 'c'}
            },

        },
        {'S'}
    }),
            BuildingException);
}

TEST(GrammarTest, ThorwOnTryCreateNonRightLinearGramar2) {
    ASSERT_THROW(RGrammarBuilder().build({
                                                 {'a', 'b', 'c'},
                                                 {'S', 'T'},
                                                 {
                                                  {
                                                          {'a','S'},
                                                          {'T', 'a'}
                                                  },
                                                       {
                                                               {'T'},
                                                               {'a', 'b', 'c'}
                                                       },

                                                 },
                                                 {'S'}
                                         }),
                 BuildingException);
}