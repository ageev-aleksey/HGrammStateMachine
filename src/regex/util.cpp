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
#include <algorithm>
#include <map>

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



//Graph<std::pair<bool, std::set<size_t>>, char> util::convertNFSMtoDFSM2(Graph<Empty, char>  &nfsm) {
//    Graph<std::pair<bool, std::set<size_t>>, char> result;
//    std::queue<std::set<size_t>> dontProcessedSet;
//     std::set<size_t> first_set =  util::toGlueEpsilonTransition({nfsm.firstNode().getIndex()}, nfsm);
//    //std::set<size_t> reachableStates = findTransition(currentStates, nfsm)
//    dontProcessedSet.push({nfsm.firstNode().getIndex()});
//    size_t indexEndState = nfsm.lastNode().getIndex();
//    while(!dontProcessedSet.empty()) {
//        std::set<size_t> currentStates = dontProcessedSet.front();
//        dontProcessedSet.pop();
//        //выполняем склеивание епсилон переходов в одно множество подсостояний
//        currentStates = util::toGlueEpsilonTransition(currentStates, nfsm);
//        //Проверяем, что такое же состояние уже не находится в новом графе
//        //Если состояние является подмножеством какого либо подстостояния в новом графе
//        //о его так же не надо обрабатывать
//        bool isStateAlreadyProcessed = false;
//        for(auto &node : result.getNodes()) {
//            std::set<size_t> resultOfIntersection;
//            std::set_intersection(node.data.second.begin(), node.data.second.end(),
//                                  currentStates.begin(), currentStates.end(),
//                                  std::inserter(resultOfIntersection, resultOfIntersection.begin()));
//            if(resultOfIntersection.size() == currentStates.size()) {
//                isStateAlreadyProcessed = true;
//                break;
//            }
////            if(node.data.second == currentStates) {
////                isStateAlreadyProcessed = true;
////                break;
////            }
//        }
//        if(isStateAlreadyProcessed) {
//            continue;
//        }
//        //Если такое объединенное состояние отстутствует в графе то добавляем его
//        // 1. Проверяем. Содержит ли объединенное состояние конечного состояние исходного графа
//        bool isEndedState = false;
//        if(currentStates.find(indexEndState) != currentStates.end()) {
//            //новое состояние содержит конечное состояние исходного графа
//            //значит новое состояние будет конечным
//            isEndedState = true;
//        }
//        //2. Создаем новое состояние
//        auto newState = result.addNodeInBack({isEndedState, currentStates});
//        //3. Необходимо найти те состояния в новом графе, с которыми новый узел связан через подсостояние.
//        for(size_t state : currentStates) {
//            //Проходим по связанным состоянием с текущем состоянием
//            for(Graph<Empty, char>::Link &reachable_state_link : nfsm.getNodeByIndex(state).getLinks()) {
//                //если это связь епсилон перехода, то ее не надо обрабатывать
//                if(reachable_state_link.data == util::EPSILON) {
//                    continue;
//                }
//                size_t reachable_state = reachable_state_link.node.getIndex();
//                //проверяем, явялется ли достежимое состояние(reachable_state) из текущего состояния(state)
//                //подсостоянием состояние нового графа. Если это так, то создаем связь
//                for(Graph<std::pair<bool, std::set<size_t>>, char>::Node &newGraphStateNode : result.getNodes()) {
////                    if(newGraphStateNode.index == newState.getIndex()) {
////                        //проверять достижимость к себе нет необходимости
////                        continue;
////                    }
//                    std::set<size_t> &sub_states_set = newGraphStateNode.data.second;
//                    //если достижимое состояние(reachable_state) является подсостоянием, то создаем связь
//                    if(sub_states_set.find(reachable_state) != sub_states_set.end()) {
//                        result.addLink(newState, result.getNodeByIndex(newGraphStateNode.index), reachable_state_link.data);
//                    }
//                }
//            }
//        }
//
//        //4.Необходимо найти те состояния в новом графе, которые связаны с новым состоянием через подсостояния.
//        for(Graph<std::pair<bool, std::set<size_t>>, char>::Node node : result.getNodes()) {
//            if(node.index == newState.getIndex()) {
//                //Проверять достежимось из от новый вершины к новой вершине нет необходимости
//                continue;
//            }
//            std::set<size_t> &substates = node.data.second;
//            size_t index_current_old_node = node.index;
//            for(size_t substate : substates) {
//                std::set<size_t> &substates_newState = newState.getData().second;
//                //substate - подсостояние старой вершины нового графа
//                //substates_newState - набор подсостояние новой вершины нового графа
//                //необходимо проверить, достежимо ли какоето подсостояние новой вершины из подсостояния сарой вершины
//                for(Graph<Empty, char>::Link &link_substate : nfsm.getNodeByIndex(substate).getLinks()) {
//                    //если это связь епсилон перехода, то ее не надо обрабатывать
//                    if(link_substate.data == util::EPSILON) {
//                        continue;
//                    }
//                    size_t reachable_state = link_substate.node.getIndex();
//                    //выполняем проверку достижимости
//                    if(substates_newState.find(reachable_state) != substates_newState.end()) {
//                        result.addLink(result.getNodeByIndex(node.index), newState, link_substate.data);
//                    }
//                }
//            }
//        }
//
//        //5. Необходимо сформировать множества состояний доступные  из текущего состояния
//        for(size_t state : currentStates) {
//            std::set<size_t> reachable_states;
//            for(Graph<Empty, char>::Link &link : nfsm.getNodeByIndex(state).getLinks()) {
//                reachable_states.insert(link.node.getIndex());
//            }
//            dontProcessedSet.push(reachable_states);
//        }
//
//
//    }
//
//    return result;
//
//}

Graph<std::pair<bool, std::set<size_t>>, char> util::convertNFSMtoDFSM2(Graph<Empty, char>  &nfsm) {
     std::queue<std::set<size_t>> dontProcessedSet;
     std::vector<std::set<size_t>> alreadyProcessed;
     std::set<size_t> first_set =  util::toGlueEpsilonTransition({nfsm.firstNode().getIndex()}, nfsm);
    //std::set<size_t> reachableStates = findTransition(currentStates, nfsm)
    dontProcessedSet.push(first_set);
    size_t indexEndState = nfsm.lastNode().getIndex();
    while(!dontProcessedSet.empty()) {
        std::set<size_t> setStates = dontProcessedSet.front();
        dontProcessedSet.pop();
        //1 проверяем, что такое множество уже не обработано
        bool isAlready = false;
        for(auto itr = alreadyProcessed.begin(); itr != alreadyProcessed.end(); itr++) {
            std::set<size_t> intersect_result;
            std::set_intersection(setStates.begin(),setStates.end() ,
                                  itr->begin(), itr->end(),
                                 std::inserter(intersect_result, intersect_result.begin()));
          //  if(intersect_result == setStates || intersect_result == *itr) {
                if(intersect_result == setStates) {
                    //  if(setStates == *itr) {
                    isAlready = true;
                    break;
                }
//            } else if(intersect_result == *itr) {
//                   *itr = setStates;
//                    isAlready = true;
//                    break;
//                }
        }
        if(isAlready) {
            continue;
        }
        alreadyProcessed.push_back(setStates);

        //формируем новые множества, которые достижимы из state по одному и тому же символу
        std::map<char, std::set<size_t>> reachableStates;
        for(auto &state : setStates) {
           auto nodeOfState = nfsm.getNodeByIndex(state);

           for(auto &link : nodeOfState.getLinks()) {
               if(link.data == util::EPSILON) continue;
               reachableStates[link.data].insert(link.node.getIndex());
           }
        }
        for(auto el : reachableStates) {
            dontProcessedSet.push(util::toGlueEpsilonTransition(el.second, nfsm));
        }
    }

    Graph<std::pair<bool, std::set<size_t>>, char> g;
    for(auto el: alreadyProcessed) {
        bool isTerminal = (el.find(nfsm.lastNode().getIndex()) != el.end());
        g.addNodeInBack({isTerminal, el});
    }

    for(auto nItr = g.begin(); nItr != g.end(); ++nItr ) {
        //рассматриваем каждое подсостояние
        for(auto substate: nItr.getData().second) {
            //Рассматриваем связи подсостояния в исходном графе
            for(auto &oldLink : nfsm.getNodeByIndex(substate).getLinks()) {
                //эпсилон переходы не рассматриваем
                if(oldLink.data == util::EPSILON) continue;
                //проверяем, что переход по такому символу отсутсвтует
                bool linkIsAlready = false;
                for(auto &newLinks : nItr.getLinks()) {
                    if(newLinks.data == oldLink.data) {
                        linkIsAlready = true;
                        break;
                    }
                }
                if(linkIsAlready) continue;
                //Ищем в каком состоянии нового графа, находится достижимое подсостояние
                bool isSelf = false;
                //Сначало проверим, можем ли мы перейти сами в себя
                if(nItr.getData().second.find(oldLink.node.getIndex()) != nItr.getData().second.end()) {
                    isSelf = true;
                }
                for(auto nodeIteratorFind = g.begin(); nodeIteratorFind != g.end(); ++nodeIteratorFind) {
                    if(nodeIteratorFind.getData().second.find(oldLink.node.getIndex()) != nodeIteratorFind.getData().second.end()){
                        //мы нашли состояние, которое содержит достежимое подсостояние
                        if(isSelf) {
                            if(nodeIteratorFind.getData().second.size() > nItr.getData().second.size()) {
                                isSelf = false;
                                g.addLink(nItr, nodeIteratorFind, oldLink.data);
                                break;
                            }
                        } else {
                            g.addLink(nItr, nodeIteratorFind, oldLink.data);
                            isSelf = false;
                            break;
                        }

                    }
                }
                if(isSelf) {
                    g.addLink(nItr, nItr, oldLink.data);
                }

            }
        }

    }
    return g;
}


void nodeRepresentToDOT(const Graph<std::pair<bool, std::set<size_t>>, char>::Node &node, std::stringstream &format) {
    format << "\"";
    if(node.data.first) {
        format << "*";
    }
    format << node.index << " {";
    for(auto itr = node.data.second.begin(); itr != --(node.data.second.end()); itr++) {
        format << *itr << "; ";
    }
    if(node.data.second.begin() != node.data.second.end()) {
        format << *(--node.data.second.end());
    }
    format << "}\"";
}

template<>
std::string util::graphToDOT(Graph<std::pair<bool, std::set<size_t>>, char> &g) {
    std::string dot("digraph {\n");
    auto& nodes = g.getNodes();
    for(auto &el : nodes) {
        for(auto &link : el.links) {
           std::stringstream format;
            nodeRepresentToDOT(el, format);
            format << " -> ";
            nodeRepresentToDOT(link.node.getNode(), format);
            format << " [label=\"" << link.data << "\"]\n";
            dot.append(format.str());
        }
        if(el.links.empty()) {
            dot.append(std::to_string(el.index) + "\n");
        }
    }
    dot.append("}\n");
    return dot;
}


std::vector<std::vector<bool>> util::buildTableOfNotEquivalentVertex(const std::vector<bool> &isTerminal,
        const std::vector<std::map<char, std::vector<size_t>>> &tableOfBackLink, const std::set<char> &alphabet) {
    std::queue<std::pair<size_t, size_t>> queue;
    size_t n = isTerminal.size();
    std::vector<std::vector<bool>> marked;
    marked.resize(n);
    for(size_t i = 0; i < n ; i++) {
        marked[i].resize(n, false);
    }
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < n; j++) {
            if((!marked[i][j]) && (isTerminal[i] != isTerminal[j])) {
                marked[i][j] = true;
                marked[j][i] = true;
                queue.push({i, j});
            }
        }
    }

    while(!queue.empty()) {
        std::pair<size_t, size_t> p = queue.front();
        queue.pop();
        for(char c : alphabet) {
            auto &l1 = tableOfBackLink[p.first];
            auto &l2 = tableOfBackLink[p.second];
            auto element1 = l1.find(c);
            auto element2 = l2.find(c);
            if(element1 == l1.end()) continue;
            for(size_t r : (*element1).second) {
                if(element2 == l2.end()) continue;
                for(size_t s : (*element2).second) {
                    if(r == s) {
                        continue;
                    }
                    if((!marked[r][s])) {
                        marked[r][s] = true;
                        marked[s][r] = true;
                        queue.push({r ,s});
                    }
                }
            }
        }

    }
    return marked;
}

std::vector<std::map<char, std::vector<size_t>>> util::buildTableOfBackLink(Graph<std::pair<bool, std::set<size_t> >, char> &g) {
    std::vector<std::map<char, std::vector<size_t>>> table;
    size_t n = g.numNodes();
    table.resize(n);
    for(auto &el : g.getNodes()) {
        for(auto &link : el.links) {
            table[link.node.getIndex()][link.data].push_back(el.index);
        }
    }
    return table;
}

void util::addDevilsVertex(Graph<std::pair<bool, std::set<size_t> >, char> &dfsm) {
    std::set<char> alphabet = dfsm.getUniqueLinkData();
    auto v = dfsm.addNodeInFront({false, {-1U}});
    for(auto node = dfsm.begin(); node != dfsm.end(); ++node) {
        for(auto s : alphabet) {
            //добавляем связь только в том случае, если связи с таким символом нет
           bool isLinkAlready = false;
            for(auto &link: node.getLinks()) {
                if(link.data == s) {
                    isLinkAlready = true;
                    break;
                }
            }
            if(!isLinkAlready) {
                dfsm.addLink(node, v, s);
            }

        }
    }
}

Graph<std::pair<bool, std::set<size_t>>, char> util::minimizeDFSM(Graph<std::pair<bool, std::set<size_t> >, char> &dfsm) {
    std::set<char> alphabet = dfsm.getUniqueLinkData();
    //size_t n = dfsm.numNodes();
    //1. Добавляем универсальную вершину, в которую имеют переход все состояния по всем символам алфавита автомата
    addDevilsVertex(dfsm);
    size_t n = dfsm.numNodes();
    //2. Строим таблицу обратных ребер
    std::vector<std::map<char, std::vector<size_t>>> tableOfBackLink = buildTableOfBackLink(dfsm);
    //3 строим таблицу не эквивалентных вершин графа
    std::vector<bool> isTerminal(n);
    size_t i = 0;
    for(auto itr = dfsm.begin(); itr != dfsm.end(); ++itr) {
        isTerminal[i] = itr.getData().first;
        i++;
    }
    std::vector<std::vector<bool>> tableNotEquivalent = buildTableOfNotEquivalentVertex(isTerminal,
                                                                                        tableOfBackLink, alphabet);
    //4. По таблице фомируем новый граф
    //  - В строке таблицы не помеченные столбцы являются эквивалентными вершинами.
    //  - Создаем вершину, которая будет заменой эквивалентных вершин.
    //  - устанавливаем связи между вершинами, подвершины которых связаны в исходном графе
    std::set<std::set<size_t>>equivalentSets;
    for(size_t j = 1; j < n; j++) {
        std::set<size_t> set;
        set.insert(j);
        for(size_t k = 1; k < n; k++) {
            if(tableNotEquivalent[j][k] == false) {
                set.insert(k);
            }
        }
        equivalentSets.insert(std::move(set));
    }
    Graph<std::pair<bool, std::set<size_t>>, char> minFSM;
    //Создание узлов содержащие классы эквивалентности
    for(auto &set : equivalentSets) {
        bool terminalNode = false;
        for(size_t nodeIndex : set) {
            if(isTerminal[nodeIndex]) {
                terminalNode = true;
                break;
            }
        }
        minFSM.addNodeInBack({terminalNode, set});
    }

    //Создаем связи между узлами
    for(auto node = minFSM.begin(); node != minFSM.end(); ++node) {
        std::set<size_t> &subset = node.getData().second;
        for(size_t index : subset) {
            //ищем какие связи существовали в исходном графе
            auto oldNode = dfsm.getNodeByIndex(index);
            //проходим по связям данного узла
            for(auto &oldLink : oldNode.getLinks()) {
                //находм узел с подмножеством, содержащем индекс свзяного узла и создаем связь
                for(auto node2 = minFSM.begin(); node2 != minFSM.end(); ++node2) {
                   /* if(node == node2) {
                        continue;
                    }*/
                    //если узел в подмножестве содержит этот индекс, то создаем связь между новыми узлами
                    if(node2.getData().second.find( oldLink.node.getIndex()) != node2.getData().second.end()) {
                        //Необходимо, проверить, что мы не дублируем связь
                        //Если переход по такому символу уже существует, значит переход не надо добалвять.
                        //Это верно, так как мы работаем с детерминированным автоматом
                        bool isLinkAlready = false;
                        for(auto &l : node.getLinks()) {
                            if(l.data == oldLink.data) {
                                isLinkAlready = true;
                                break;
                            }
                        }

                        if(isLinkAlready) continue;

                        minFSM.addLink(node, node2, oldLink.data);
                    }
                }
            }
        }
    }
    return minFSM;
}

std::vector<std::map<char, size_t>> util::buildConversionTable(Graph<std::pair<bool, std::set<size_t>>, char> &g) {
    std::set<char> alphabet = g.getUniqueLinkData();
    std::map<char, size_t> init;
    for(char s : alphabet) {
        init[s] = -1;
    }
    std::vector<std::map<char, size_t>> result(g.numNodes(), init);
    for(auto itr = g.begin(); itr != g.end(); ++itr) {
        for(auto &link : itr.getLinks()) {
            result[itr.getIndex()][link.data] = link.node.getIndex();
        }
    }
    return result;
}