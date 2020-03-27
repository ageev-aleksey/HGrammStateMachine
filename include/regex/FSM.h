//
// Created by nrx on 26.03.2020.
//

#ifndef STATE_MACHINE_FSM_H
#define STATE_MACHINE_FSM_H
#include "regex/Graph.h"
#include <unordered_set>


template<typename NodeInfo>
class FSM {
public:
    struct Link {
        bool operator==(const Link &other) const {
            return (firstNode == other.firstNode) && (secondNode == other.secondNode) &&
                    (symbol == other.symbol);
        }
        size_t firstNode;
        size_t secondNode;
        char symbol;
    };
    struct Node {
        Node() {
            isEnded = false;
        }
        Node(const Node& node) : data(node.data), isEnded(node.isEnded) {}

        NodeInfo data;
        bool isEnded;
    };
    FSM() {

    }
    FSM(const FSM &fsm) : graph(fsm.grpah) {
    }
    FSM(const Graph<Node, char> &graph) : graph(graph) {
    }

    std::unordered_set<char> getAlphabet() {
        std::unordered_set<char> alphabet;
        for(auto  &node : graph.getNodes()) {
            for(auto &link : node.links) {
                alphabet.insert(link.data);
            }
        }
        return alphabet;
    }

    std::unordered_set<Link> getLinks() {
        std::unordered_set<Link> links;
        for( auto  &node : graph.getNodes()) {
            size_t nIndex = node.index;
            for( auto &link : node.links) {
                links.insert({nIndex, link.node.getIndex(), link.data});
            }
        }
        return links;
    }

    const Node &getNode(size_t index) const {
        return graph.getNodeByIndex(index).getData();
    }

    size_t nodesCount() const {
        return graph.lastNode().getIndex() + 1;
    }
private:

    Graph<Node, char> graph;
};


namespace std {

    template<>
    struct hash <FSM<Empty>::Link> {
        size_t operator()(const FSM<Empty>::Link &link) const {
            return 115249*(101*link.firstNode + 563*link.secondNode+7*link.symbol);
        }
    };
}

#endif //STATE_MACHINE_FSM_H
