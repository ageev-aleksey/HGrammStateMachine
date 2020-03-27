//
// Created by nrx on 21.03.2020.
//

//#include "regex/Graph.h"
//#include "gtest/gtest.h"
//#include <unordered_set>
//#include <utility>
//
//namespace std {
//    template<>
//    struct hash<std::pair<int, int>> {
//        size_t operator()(const std::pair<int, int>& p) const {
//            return 101 * (p.first + p.second);
//        }
//    };
//}
//
//template<typename T1, typename T2>
//void checkLinks(const Graph<T1, T2> &g, const  std::unordered_set<std::pair<T1, T2>> &graph_links) {
//    const std::list<Graph<int, int>::Node> &n = g.getNodes();
//
//    for(const auto &el : n) {
//        for(const auto &l : el.links) {
//            ASSERT_TRUE(graph_links.find({el.data, l.node.getData()}) != graph_links.end());
//        }
//    }
//}
//
//
//TEST(TestGraph, CreateGraph) {
//    std::unordered_set<std::pair<int, int>> graph_links{{1, 2}, {1, 3}};
//    Graph<int, int> g;
//    Graph<int, int>::iterator v1 = g.addNode(1);
//    Graph<int, int>::iterator v2 = g.addNode(2);
//    Graph<int, int>::iterator v3 = g.addNode(3);
//    g.addLink(v1, v2, 0);
//    g.addLink(v1, v3, 0);
//
//    checkLinks(g, graph_links);
//
//    /*for(const auto &el : n) {
//        for(const auto &l : el.links) {
//            std::cout << el.data << "-->" << l.node.getData() << std::endl;
//        }
//        if(el.links.empty()) {
//            std::cout << el.data << std::endl;
//        }
//    }*/
//}
//
//TEST(TestGraph, GraphConcatenate) {
//    Graph<int, int> g1;
//    Graph<int, int> g2;
//    Graph<int, int>::iterator v11 =g1.addNode(11);
//    Graph<int, int>::iterator v12 =g1.addNode(12);
//    Graph<int, int>::iterator v13 =g1.addNode(13);
//
//    Graph<int, int>::iterator v21 =g2.addNode(21);
//    Graph<int, int>::iterator v22 =g2.addNode(22);
//    Graph<int, int>::iterator v23 =g2.addNode(23);
//
//    g1.addLink(v11, v12, 1);
//    g1.addLink(v12, v13, 2);
//
//    g2.addLink(v21, v22, 3);
//    g2.addLink(v22, v23, 4);
//
//    checkLinks(g1, {{11, 12}, {12, 13}});
//    checkLinks(g2, {{21, 22}, {22, 23}});
//
//    Graph<int, int> g3 = Graph<int,int>::concatenate(v13, v21, 5);
//
//    ASSERT_TRUE(g1.getNodes().empty());
//    ASSERT_TRUE(g2.getNodes().empty());
//
//    checkLinks(g3, {{11, 12}, {12, 13}, {13, 21}, {21, 22}, {22, 23}});
//}
//
//TEST(TestGraph, CheckForAddingForeignVertexToTheGraph) {
//    Graph<int, int> g1;
//    Graph<int, int> g2;
//
//    Graph<int, int>::iterator v11 = g1.addNode(11);
//    Graph<int, int>::iterator v12 = g1.addNode(12);
//
//    Graph<int, int>::iterator v21 = g2.addNode(21);
//    Graph<int, int>::iterator v22 = g2.addNode(22);
//
//    ASSERT_THROW(g1.addLink(v11, v21, 1), InvalidVertexException);
//}
