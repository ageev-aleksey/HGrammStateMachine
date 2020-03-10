//
// Created by nrx on 04.03.2020.
//
#include "grammar/Symbol.h"
#include "grammar/RGramarBuilder.h"
#include "grammar/Grammar.h"
#include "grammar/Productions.h"
//#include "grammar/SetSymbols.h"
//#include "grammar/SymbolsChain.h"
#include <iostream>
#include <unordered_set>
#include <stdexcept>

template<typename T>
void print(T v) {
    for(auto &el : v) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& stream, std::list<Symbol> s) {
    for(const auto &el : s) {
        stream << el;
    }
    return stream;
}

int main(int argc, char** argv) {

    /*SymbolsChain a{'S'}, b{'D'}, c{'S'};
    Comparator comp;
    std::cout <<  comp(a, b) << " " <<  comp(b, a) << " " << comp(a, c) << std::endl;*/
   Productions p;
    p.addProduction({'S'}, {'a', 'b'});
    p.addProduction({'S'}, {'S'});
    p.addProduction({'S'}, {'q', 'D', 'a'});
    p.addProduction({'D'}, {'a', 'b'});
    p.addProduction({'D'}, {'a', 'D'});
    p.addProduction({'D'}, {'c', 'D'});

    for(auto itr = p.begin(); itr != p.end(); ++itr){
        std::cout << "(" << (*itr).first << "; " <<(*itr).second << ")\n";
    }
   /* try {
        std::unordered_set<Symbol> terminals{'a', 'b', 'c'};
        std::unordered_set<Symbol> nonTerminals{'D', 'S', 'Q'};
        RGrammarBuilder rbuilder;
        rbuilder.setTerminals(terminals)
                .setNonTerminals(nonTerminals)
                .setAxiom('S')
                .setProduction({'S'}, {'a', 'c', 'S'})
                .setProduction({'S'}, {'b', 'D'})
                .setProduction({'D'}, {'Q'})
                .setProduction({'D'}, {'S'})
                .setProduction({'Q'}, {'a', 'b', 'c'});
      //  rbuilder.setProduction({'S'}, {'b', 'D'});
        Grammar g = rbuilder.build();
    } catch (std::exception &exp) {
        std::cout << exp.what();
    }*/





    return 0;
}
