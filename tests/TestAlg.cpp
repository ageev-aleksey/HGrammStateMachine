////
//// Created by nrx on 14.03.2020.
////
//#include "gtest/gtest.h"
//#include "grammar/Alg.h"
//#include "grammar/Grammar.h"
//#include "grammar/RGramarBuilder.h"
//#include "grammar/Symbol.h"
//
//
//TEST(AlgTest, TestCreateStandartEquatuin) {
//    Grammar g =  RGrammarBuilder().build({
//                                                 {'0', '1'},
//                                                 {'S', 'A', 'B'},
//                                                 {
//                                                  {
//                                                          {'S'},
//                                                          {'0', 'A'}
//                                                  },
//                                                       {
//                                                               {'S'},
//                                                               {'1', 'S'}
//                                                       },
//                                                            {
//                                                                    {'S'},
//                                                                    {'e'}
//                                                            },
//                                                         {
//                                                                 {'A'},
//                                                                 {'0', 'B'}
//                                                         },
//                                                         {
//                                                                 {'A'},
//                                                                 {'1', 'A'}
//                                                         },
//                                                         {
//                                                                 {'B'},
//                                                                 {'0', 'S'}
//                                                         },
//                                                         {
//                                                                 {'B'},
//                                                                 {'e','B'}
//                                                         },
//
//                                                 },
//                                                 {'S'}
//                                         });
//    auto m = Alg::createStandardSystemEquation(g);
//    for(const auto &el : m.second) {
//        std::cout << "(" << el.first << "; " << el.second << ") ";
//    }
//    std::cout << std::endl;
//    for(size_t i = 0; i < m.first.getNrow(); ++i) {
//        for(size_t j = 0; j < m.first.getNcol(); ++j) {
//            for(const auto &el : m.first.at(i, j)) {
//                std::cout << el;
//            }
//            if(m.first.at(i, j).size() == 0) {
//                std::cout << Symbol::EMPTY_SYMBOL;
//            }
//            std::cout << " | ";
//        }
//        std::cout << std::endl;
//    }
//
//}
//
//
//
//TEST(AlgTest, TestSolveStandartEquaton) {
//    Grammar g = RGrammarBuilder().build({
//                                                {'0', '1'},
//                                                {'S', 'A', 'B'},
//                                                {
//                                                 {
//                                                         {'S'},
//                                                         {'0', 'A'}
//                                                 },
//                                                      {
//                                                              {'S'},
//                                                              {'1', 'S'}
//                                                      },
//                                                           {
//                                                                   {'S'},
//                                                                   {'e'}
//                                                           },
//                                                        {
//                                                                {'A'},
//                                                                {'0', 'B'}
//                                                        },
//                                                        {
//                                                                {'A'},
//                                                                {'1', 'A'}
//                                                        },
//                                                        {
//                                                                {'B'},
//                                                                {'0', 'S'}
//                                                        },
//                                                        {
//                                                                {'B'},
//                                                                {'e', 'B'}
//                                                        },
//
//                                                },
//                                                {'S'}
//                                        });
//    auto m = Alg::createStandardSystemEquation(g);
//    auto matrix = Alg::solveStandardSystemEquation(m.first);
//    for(size_t i = 0; i < matrix.getNrow(); ++i) {
//        size_t j = 0;
//        for( ; j < matrix.getNcol(); ++j) {
//            std::cout << matrix.at(i, j)  << " | ";
//        }
//        if(matrix.at(i, j).empty()) {
//            std::cout << Symbol::EMPTY_SYMBOL  << " | ";
//        }
//        std::cout << std::endl;
//    }
//
//}