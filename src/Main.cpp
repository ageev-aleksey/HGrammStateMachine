////
//// Created by nrx on 04.03.2020.
////

#include "regex/Matcher.h"
#include <iostream>
#include <fstream>

void enterRegex(std::string &regex) {
    std::cout << "-- Enter regular expression:\n";
    std::cout << "> ";
    std::cin >> regex;
}


int main() {
    std::string regex;
    std::string str;
    std::ofstream file1("NFSM.dot");
    std::ofstream file2("DFSM.dot");
    std::ofstream file3("FSM.dot");
    enterRegex(regex);
    Matcher m = Matcher::compile(regex, file1, file2, file3);
    file1.close();
    file2.close();
    file3.close();
   std::cout << "-- Enter string for matching (\\q - for exit;):\n";
   std::cout << "> ";
   while(std::cin >> str) {
        if(str == "\\q") {
            break;
        } else if(m.match(str)) {
           std::cout << "string is matching\n";
       } else {
           std::cout << "string isn't matching\n";
       }
       std::cout << "-- Enter string for matching (\\q - for exit; \\r - change regex):\n";
       std::cout << "> ";
   }

    std::cout << "good by!...\n";
    return 0;
}



















//#include "grammar/Symbol.h"
//#include "grammar/RGramarBuilder.h"
//#include "grammar/Grammar.h"
//#include "grammar/Productions.h"
////#include "grammar/SetSymbols.h"
////#include "grammar/SymbolsChain.h"
//#include <iostream>
//#include <unordered_set>
//#include <stdexcept>
//#include <stack>
//
//#include "regex/Graph.h"
//#include "regex/util.h"
//
//template<typename T>
//void print(T v) {
//    for(auto &el : v) {
//        std::cout << el << ' ';
//    }
//    std::cout << std::endl;
//}
//
//std::ostream& operator<<(std::ostream& stream, std::list<Symbol> s) {
//    for(const auto &el : s) {
//        stream << el;
//    }
//    return stream;
//}
//
//int main(int argc, char** argv) {
//    std::stack<Graph<Empty, char>> stack;
//    {
//        Graph<Empty, char> g1;
//        auto tmp11 = g1.addNode(Empty{});
//        auto tmp12 = g1.addNode(Empty{});
//        g1.addLink(tmp11, tmp12, 'a');
//        stack.push(g1);
//        Graph<Empty, char> g2;
//        auto tmp21 = g2.addNode(Empty{});
//        auto tmp22 = g2.addNode(Empty{});
//        g2.addLink(tmp21, tmp22, 'b');
//        stack.push(g2);
//    }
//    Graph<Empty, char> g3 = stack.top();
//    std::cout << util::graphToDOT(g3);
//    stack.pop();
//    Graph<Empty, char> g4 = stack.top();
//    stack.pop();
//    std::cout << util::graphToDOT(g4);
//    auto v3 = g3.firstNode();
//    auto v4 = g4.lastNode();
//    g4.concatenate(g3);
//    g4.addLink(v4, v3, 'e');
//    std::cout << util::graphToDOT(g4);
////    Graph<Empty, char> g;
////    auto v1 = g.addNode(Empty{});
////    auto v2 = g.addNode(Empty{});
////    auto v3 = g.addNode(Empty{});
////    g.addLink(v1, v2, 'a');
////    g.addLink(v2, v3, 'b');
////    g.addLink(v3, v1, 'c');
////    std::string dot = util::graphToDOT(g);
////    std::cout << dot << std::endl;
////
////    Graph<Empty, char> g2;
////    auto v21 = g.addNode(Empty{});
////    auto v22 = g.addNode(Empty{});
////    g2.addLink(v22, v21, 'e');
////
////    g.concatenate(g2);
////    g.addLink(v22, v1, 'k');
////    dot = util::graphToDOT(g2);
////    std::cout << dot << std::endl;
//
//    /*SymbolsChain a{'S'}, b{'D'}, c{'S'};
//    Comparator comp;
//    std::cout <<  comp(a, b) << " " <<  comp(b, a) << " " << comp(a, c) << std::endl;*/
//   /*Productions p;
//    p.addProduction({'S'}, {'a', 'b'});
//    p.addProduction({'S'}, {'S'});
//    p.addProduction({'S'}, {'q', 'D', 'a'});
//    p.addProduction({'D'}, {'a', 'b'});
//    p.addProduction({'D'}, {'a', 'D'});
//    p.addProduction({'D'}, {'c', 'D'});
//
//    for(auto itr = p.begin(); itr != p.end(); ++itr){
//        std::cout << "(" << (*itr).first << "; " <<(*itr).second << ")\n";
//    }*/
//   /* try {
//        std::unordered_set<Symbol> terminals{'a', 'b', 'c'};
//        std::unordered_set<Symbol> nonTerminals{'D', 'S', 'Q'};
//        RGrammarBuilder rbuilder;
//        rbuilder.setTerminals(terminals)
//                .setNonTerminals(nonTerminals)
//                .setAxiom('S')
//                .setProduction({'S'}, {'a', 'c', 'S'})
//                .setProduction({'S'}, {'b', 'D'})
//                .setProduction({'D'}, {'Q'})
//                .setProduction({'D'}, {'S'})
//                .setProduction({'Q'}, {'a', 'b', 'c'});
//      //  rbuilder.setProduction({'S'}, {'b', 'D'});
//        Grammar g = rbuilder.build();
//    } catch (std::exception &exp) {
//        std::cout << exp.what();
//    }*/
//
//
//
//
//
//    return 0;
//}
