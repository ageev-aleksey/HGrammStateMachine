//
// Created by nrx on 21.03.2020.
//

#ifndef STATE_MACHINE_ALGORITHMS_H
#define STATE_MACHINE_ALGORITHMS_H
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <map>
#include "regex/Graph.h"
#include "regex/FSM.h"
#include <utility>

namespace util {

    constexpr char EPSILON = 'e';

    /**
     * Преобразование стандартной записи регулярного выражения в обратную польскую запись
     * Поддерживаемые операции: \-дизъюнкция,; &-конкатенация; (); *-замыкание Клини.
     * @param common_notation
     * @return
     */
    std::string convertToRPN(const std::string &common_notation);
    /**
     * Формирования DOT-описаня графа для grapviz
     * @param g - граф, который необходимо нарисовать
     * @return DOT-описаня графа
     */
    template<typename NodeData>
    std::string graphToDOT(Graph<NodeData, char> &g) {
        std::string dot("digraph {\n");
        const auto& nodes = g.getNodes();
        for(const auto &el : nodes) {
            for(const auto &link : el.links) {
                std::stringstream format;
                format << el.index << "->" << link.node.getIndex() << " [label=\"" << link.data << "\"]\n";
                dot.append(format.str());
            }
            if(el.links.empty()) {
                dot.append(std::to_string(el.index) + "\n");
            }
        }
        dot.append("}\n");
        return dot;
    }

    template<>
    std::string graphToDOT(Graph<std::pair<bool, std::set<size_t>>, char> &g);

    std::set<size_t> toGlueEpsilonTransition(const std::set<size_t> &cs, Graph<Empty, char> &g);

    /**
     * Построение графа на основе регулярного выражения с помощью алгоритма "Конструктор Томпсона"
     * Поддерживаемые операции: \-дизъюнкция,; &-конкатенация; (); *-замыкание Клини.
     * СпецСимволы: e - пустая цепочка
     * @param regex - регулярное выражение в обратной польской записи
     * @return
     */
    Graph<Empty, char> graphFromRegex(const std::string regex);

   // Graph<std::pair<bool, std::unordered_set<size_t>>, char>  convertNFSMtoDFSM(const Graph<Empty, char> &nfa);
    Graph<std::pair<bool, std::set<size_t>>, char> convertNFSMtoDFSM2(Graph<Empty, char>  &nfsm);

    std::vector<std::vector<bool>> buildTableOfNotEquivalentVertex(const std::vector<bool> &isTerminal,
            const std::vector<std::map<char, std::vector<size_t>>> &tableOfBackLink, const std::set<char> &alphabet);

    std::vector<std::map<char, std::vector<size_t>>> buildTableOfBackLink(Graph<std::pair<bool, std::set<size_t> >, char> &g);
    Graph<std::pair<bool, std::set<size_t>>, char> minimizeDFSM(Graph<std::pair<bool, std::set<size_t>>, char> &dfsm);
    std::vector<std::map<char, size_t>> buildConversionTable(Graph<std::pair<bool, std::set<size_t>>, char> &g);
    void addDevilsVertex(Graph<std::pair<bool, std::set<size_t> >, char> &dfsm);
}

#endif //STATE_MACHINE_ALGORITHMS_H
