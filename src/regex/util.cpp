//
// Created by nrx on 21.03.2020.
//


#include <string>
#include <sstream>
#include "regex/util.h"
#include "regex/Graph.h"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <iostream>
#include <queue>
#include <set>
#include <utility>

namespace std {
    template<>
    struct hash<std::pair<char, size_t>> {
        size_t operator()(const std::pair<char, size_t>& p) const {
            return 101 * (p.first + p.second);
        }
    };
}
/*
class Pointer {
public:
    Pointer(const std::pair<const char, int> &value) : pair(value){
    }
    Pointer(const std::unordered_map<char, int>::iterator &i) : pair({0, 0}){
        itr = i;
    }

    std::pair<const char, int> operator*() {
        if(pair == std::pair<const char, int>{0, 0}) {
            return *itr;
        } else {
            return pair;
        }
    }

    std::pair<const char, int>* operator->() {
        if(pair == std::pair<const char, int>{0, 0}) {
            return &(*itr);
        } else {
            return &pair;
        }
    }


private:
    std::pair<const char, int> pair;
    std::unordered_map<char, int>::iterator itr;
};*/

void put_operation(std::stack<std::pair<char, size_t>> &stack,const std::unordered_map<char, int>::iterator &op, std::string &converted) {
    if(stack.empty() || stack.top().second < op->second) {
        stack.push(*op);
    } else if (op->first == '(') {
        stack.push(*op);
    } else if (op->first == ')') {
        while(stack.top().first != '(') {
            if(stack.empty()) {
                throw std::logic_error("SyntaxError: string contain a closing bracket without opening bracket");
            }
            converted.push_back(stack.top().first);
            stack.pop();
        }
        stack.pop();//удаление открывающейся скобки
    } else {

        while(!stack.empty() && stack.top().second >= op->second) {
            converted.push_back(stack.top().first);
            stack.pop();
        }
        stack.push(*op);
    }
}


std::string util::convertToRPN(const std::string &commonNotation) {
    std::unordered_map<char, int> operations {{'(', 1}, {')', 1}, {'|', 2}, {'&', 3}, {'*', 4}};
    std::string converted;
    std::stack<std::pair<char, size_t>> stack;
    bool isBeforeOperation = true;
    for(const auto &el : commonNotation) {
        std::unordered_map<char, int>::iterator  op;
        if((op = operations.find(el)) == operations.end()) {
           /* if(!isBeforeOperation) { // если подряд идут символы, значит применяется операция конкатенации
                put_operation(stack, operations.find('&'), converted);
                isBeforeOperation = true;
            }*/
            isBeforeOperation = false;
            converted.push_back(el);
        } else {
            put_operation(stack, op, converted);
            /*if(op->first == '(' || op->first == ')') {
                isBeforeOperation = false;
            } else {
                isBeforeOperation = true;
            }*/
            isBeforeOperation = true;

        }
    }
    while(!stack.empty()) {
        converted.push_back(stack.top().first);
        stack.pop();
    }
    return converted;
}




using regexOp = void(*)(std::stack<Graph<Empty, char>>&);

void regex_concatenation(std::stack<Graph<Empty, char>> &stack) {
    Graph<Empty, char> second = stack.top();
    stack.pop();
    Graph<Empty, char> first = stack.top();
    stack.pop();
    Graph<Empty, char>::iterator firstNodeSecondGraph = second.firstNode();
    Graph<Empty, char>::iterator lastNodeFirstGraph = first.lastNode();
    first.concatenate(second);
    first.addLink(lastNodeFirstGraph, firstNodeSecondGraph, util::EPSILON);
    stack.push(first);
}

void regex_starOfKlini(std::stack<Graph<Empty, char>> &stack) {
    Graph<Empty, char> &g = stack.top();
    auto f = g.firstNode();
    auto l = g.lastNode();
    g.addLink(l, f, util::EPSILON);
    auto firstEps = g.addNodeInFront(Empty{});
    auto lastEps = g.addNodeInBack(Empty{});
    g.addLink(firstEps, f, util::EPSILON);
    g.addLink(l, lastEps, util::EPSILON);
    g.addLink(firstEps, lastEps, util::EPSILON);
}

void regex_disjunction(std::stack<Graph<Empty, char>> &stack) {
    Graph<Empty, char> second = stack.top();
    stack.pop();
    Graph<Empty, char> first = stack.top();
    stack.pop();
    Graph<Empty, char>::iterator firstNodeSecondGraph = second.firstNode();
    Graph<Empty, char>::iterator lastNodeSecondGraph = second.lastNode();
    Graph<Empty, char>::iterator firstNodeFirstGraph = first.firstNode();
    Graph<Empty, char>::iterator lastNodeFirstGraph = first.lastNode();

    first.concatenate(second);
    auto epsFirst = first.addNodeInFront(Empty{});
    auto epsLast = first.addNodeInBack(Empty{});
    first.addLink(epsFirst, firstNodeFirstGraph, util::EPSILON);
    first.addLink(epsFirst, firstNodeSecondGraph, util::EPSILON);
    first.addLink(lastNodeFirstGraph, epsLast, util::EPSILON);
    first.addLink(lastNodeSecondGraph, epsLast, util::EPSILON);

    stack.push(first);
}




Graph<Empty, char> util::graphFromRegex(const std::string regex) {

    std::stack<Graph<Empty, char>> stack;
    std::unordered_map<char, regexOp> operations{{'|', regex_disjunction}, {'&', regex_concatenation},
                                                 {'*', regex_starOfKlini}};
    for(const auto &el : regex) {
        std::unordered_map<char, regexOp>::iterator op;
        if((op = operations.find(el)) == operations.end()) {
            //это символ
            Graph<Empty, char> g;
            auto tmp1 = g.addNodeInBack(Empty{});
            auto tmp2 = g.addNodeInBack(Empty{});
            g.addLink(tmp1, tmp2, el);
            std::cout << "*****" << std::endl;
            std::cout << util::graphToDOT(g) << std::endl;
            std::cout << "*****" << std::endl;
            stack.push(g);
            //std::cout << util::graphToDOT(g);
        } else {
            op->second(stack);
        }
    }
    return stack.top();
}


using Graph_t = Graph<Empty, char>;
using GraphIter = Graph<Empty, char>::iterator;
namespace std {

    template<>
    struct less<GraphIter> {
        bool operator() (const GraphIter &f,const GraphIter &s) const {
            return (f.getIndex() < s.getIndex());
        }
    };

    template<>
    struct less <std::pair<GraphIter, GraphIter>> {
        bool operator()(const std::pair<GraphIter, GraphIter> &f, const std::pair<GraphIter, GraphIter> &s) const {
            less<GraphIter> c;
            return c(f.first, s.first);
        }
    };


}


bool isIn(const std::set<GraphIter> &set, const std::vector<std::set<GraphIter>> &container) {
    for(auto const &s : container) {
        bool isEqual = true;
        for(auto const &el : set) {
            if(s.find(el) == s.end()) {
                isEqual = false;
                break;
            }
        }
        if(isEqual) return true;
    }
    return false;
}

bool isIn(const GraphIter &iter, const std::set<GraphIter> &set) {
    return set.find(iter) != set.end();
}

struct GraphLink {
    GraphIter node1;
    GraphIter node2;
    char symbol;
};

namespace std {
    template<>
    struct less <GraphLink> {
        bool operator() (const GraphLink &f, const GraphLink &s) const {
            less<GraphIter> c;
            return c(f.node1, s.node1);
        }
    };
}

//Graph<std::pair<bool, std::unordered_set<size_t>>, char>  util::convertNFSMtoDFSM(const Graph<Empty, char>  &nfsm) {
//    std::vector<std::set<GraphIter>> processedSet;
//    std::queue<std::set<GraphIter>> dontProcessedSet;
//    Graph<std::pair<bool, std::unordered_set<size_t>>, char> resultGraph;
//    //std::unordered_set<FSM<Empty>::Link> graphLinks = nfsm.getLinks();
//    //std::unordered_set<char> alphabet = nfsm.getAlphabet();
//    dontProcessedSet.push({nfsm.firstNode()});
//    while(!dontProcessedSet.empty()) {
//        std::set<GraphIter> set = dontProcessedSet.front();
//        dontProcessedSet.pop();
//
//        if(isIn(set, processedSet)) {
//            continue;
//        }
//        processedSet.push_back(set);
//
//        std::set<GraphIter> newState;
//        std::set<GraphIter> reachableState;
//        std::set<GraphLink> linksOfState;
//        for(auto &state : set) {
//            newState.insert(state);
//            for(auto & state2 : state.getLinks()) {
//
//                linksOfState.insert({state, state2.node, state2.data});
//                reachableState.insert(state2.node);
//            }
//        }
//
//        auto newStateInGraph = resultGraph.addNodeInBack({false, {}});
//        for(auto &el : linksOfState) {
//          if(isIn(el.node2, newState)) {
//              resultGraph.addLink(newStateInGraph, newStateInGraph, el.symbol);
//          } else {
//              auto newOtherStateInGraph = resultGraph.addNodeInBack({false, {}});
//              resultGraph.addLink(newStateInGraph, newOtherStateInGraph, el.symbol);
//          }
//        }
//        dontProcessedSet.push(reachableState);
//    }
//
//    return resultGraph;
//}


using GraphRItr = Graph<std::pair<bool, std::set<size_t>>, char>::iterator;
using GraphR = Graph<std::pair<bool, std::set<size_t>>, char>;
using NodeIteratorR = std::list<GraphR::Node>::iterator;

std::set<size_t> util::toGlueEpsilonTransition(const std::set<size_t> &cs, Graph<Empty, char> &g) {
    //обход графа в глубину по епсилон переходам
    std::set<size_t> greyVertex;
    std::set<size_t> blackVertex;
    std::stack<std::pair<size_t, size_t>> stack;// {ИНдекс верщины, номер соседа}
    constexpr size_t NO_NEIGHBOUR_VERTEX = -1;
    for(auto &el : cs) {
        if(blackVertex.find(el) != blackVertex.end()) {
            continue;
        }
        stack.push({el, NO_NEIGHBOUR_VERTEX});
        greyVertex.insert(el);
        while(!stack.empty()) {
                std::pair<size_t, size_t> &vs = stack.top();
                if(vs.second == NO_NEIGHBOUR_VERTEX) {
                    auto vertex =  g.getNodeByIndex(vs.first);
                    if(!vertex.getLinks().empty()) {


                        //выбираем следующего непосещенного соседа связанного epsilon переходом
                        auto neighbours = vertex.getLinks();
                        auto neighbour = neighbours.begin();
                        size_t countIndex = 0;
//                        do {
//                           // neighbour++;
//                            //vs.second++;
//                            while((neighbour != neighbours.end()) && (neighbour->data != util::EPSILON)) {
//                                neighbour++;
//                                vs.second++;
//                            }
//                        }
//                        while((neighbour!= neighbours.end()) &&
//                              ((greyVertex.find(neighbour->node.getIndex()) != greyVertex.end()) ||
//                               (blackVertex.find(neighbour->node.getIndex()) != blackVertex.end())));


                        while((neighbour != neighbours.end()) &&(neighbour->data != util::EPSILON)) {
                            neighbour++;
                            countIndex++;
                        }

                        if(neighbour == neighbours.end()) {
                            //следующий непосещенный сосед с epsilon переходом отсутствует
                            greyVertex.erase(vs.first);
                            blackVertex.insert(vs.first);
                            stack.pop();

                        } else {
                            vs.second = countIndex;
                            size_t neighbourIndex = neighbour->node.getIndex();
                            if((greyVertex.find(neighbourIndex) == greyVertex.end()) &&
                               (blackVertex.find(neighbourIndex) == blackVertex.end())) {
                                greyVertex.insert(neighbourIndex);
                                stack.push({neighbourIndex, NO_NEIGHBOUR_VERTEX});
                            }
                        }

                    } else {
                        blackVertex.insert(vertex.getIndex());
                        stack.pop();
                    }

                } else {
                    auto vertex = g.getNodeByIndex(vs.first);
                    auto neighbours = vertex.getLinks();
                    if(vs.second == (neighbours.size()-1))  {
                        greyVertex.erase(vs.first);
                        blackVertex.insert(vs.first);
                        stack.pop();
                    } else {
                        //вытаскиваем из граффа индекс текущего соседа
                        auto n = neighbours.begin();
                        for(size_t i = 0; i < vs.second; i++) n++;


                        //переходим к следующему непосещенному соседу связанного epsilon переходом
                        do {
                            n++;
                            vs.second++;
                            while((n != neighbours.end()) && (n->data != util::EPSILON)) {
                                n++;
                                vs.second++;
                            }
                        }
                        while((n != neighbours.end()) &&
                             ((greyVertex.find(n->node.getIndex()) != greyVertex.end()) ||
                             (blackVertex.find(n->node.getIndex()) != blackVertex.end())));


                        if(n == neighbours.end()) {
                            //следующий сосед с epsilon переходом отсутствует
                            greyVertex.erase(vs.first);
                            blackVertex.insert(vs.first);
                            stack.pop();
                        } else {
                            size_t nIndex = n->node.getIndex();
                            //if((greyVertex.find(nIndex) == greyVertex.end()) &&
                            //   (blackVertex.find(nIndex) == blackVertex.end())) {
                             //   stack.push({nIndex, NO_NEIGHBOUR_VERTEX});
                            //}
                            greyVertex.insert(nIndex);
                            stack.push({nIndex, NO_NEIGHBOUR_VERTEX});
                        }

                    }
                }


        }
    }

    return blackVertex;
}



Graph<std::pair<bool, std::set<size_t>>, char> util::convertNFSMtoDFSM2(Graph<Empty, char>  &nfsm) {
    Graph<std::pair<bool, std::set<size_t>>, char> result;
    std::vector<GraphRItr> newSets;
    std::queue<std::set<size_t>> dontProcessedSet;
    dontProcessedSet.push({nfsm.firstNode().getIndex()});
    size_t indexEndState = nfsm.lastNode().getIndex();

   // toGlueEpsiloneTransition(currentStates, nfsm)

    //std::set<size_t> reachableStates = findTransition(currentStates, nfsm)



    

    while(!dontProcessedSet.empty()) {
        std::set<size_t> currentStates = dontProcessedSet.front();
        dontProcessedSet.pop();
        //Проверяем, что такое же состояние уже не находится в новом графе
        for(auto &node : result.getNodes()) {
            if(node.data.second == currentStates) {
                continue;
            }
        }

        //определяем епсилон переходы. склеевая их в одно состояние.
        //нужен обход графа в глубину или ширину по епсилон переходам
//        std::set<size_t> epsilonStates;
//        size_t epsilonStatesSize = 0;
//        do {
//            epsilonStatesSize = epsilonStates.size();
//            for (auto &el : currentStates) {
//                for (auto &link : nfsm.getNodeByIndex(el).getLinks()) {
//                    if (link.data == util::EPSILON) {
//                        epsilonStates.insert(link.node.getIndex());
//                    }
//                }
//            }
//            auto itr = epsilonStates.begin();
//            size_t index_state = *itr;
//            epsilonStates.erase(itr);
//            currentStates.insert(index_state);
//        }
//        while(epsilonStates.size() > epsilonStatesSize);
//
//        //currentStates.insert(epsilonStates.begin(), epsilonStates.end());

        auto newSate = result.addNodeInBack({false, currentStates});

        //Определеям. СОдержит ли состояние нового графа конечное состоеяние старого графа
        for(auto &el : currentStates) {
            if(el == indexEndState) {
                newSate.getData().first = true;
                break;
            }
        }



        //Определяем новые переходы
        std::set<size_t> reachableStates;
        for(auto &el : currentStates) {
            for(auto &link :nfsm.getNodeByIndex(el).getLinks()) {
                //if(link.data == util::EPSILON) continue;
                //Необходимо проверить, существует ли узел в новом графе, содержащий текущий узел старого граффа
                bool isContained = false;
                for( auto nodeItr = result.getNodes().begin(); nodeItr != result.getNodes().end(); nodeItr++ ) {
                    if(nodeItr->data.second.find(link.node.getIndex()) != nodeItr->data.second.end()) {
                        //новый граф, уже содержит узел старого графа
                        result.addLink(newSate, GraphRItr(nodeItr), link.data);
                        isContained = true;
                        break;
                    }
                }
                if(isContained) continue;
                //новый граф не имеет узлов ,которые содержат данный узел старого графа
                reachableStates.insert(link.node.getIndex());
            }
        }
        if(reachableStates.size() == 0) continue;
        dontProcessedSet.push(reachableStates);
        auto nexNode = result.addNodeInBack({false, reachableStates});
       // result.addLink(currentStates, reachableStates);

    }

    return result;

}
