//
// Created by nrx on 02.04.2020.
//

#include "regex/util.h"
#include "gtest/gtest.h"

TEST(TestCreateTableOfBackLink, createTable) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({false, {}});
    auto v2 = g.addNodeInBack({false, {}});
    g.addLink(v1, v0, 'a');
    g.addLink(v2,  v0, 'a');
    g.addLink(v0, v0, 'a');

    std::vector<std::map<char, std::vector<size_t>>> table = util::buildTableOfBackLink(g);
    std::vector<std::map<char, std::vector<size_t>>> res = {{ { 'a', {0, 1, 2} } }, {}, {}};
    ASSERT_EQ(table, res);
}

TEST(TestCreateTableOfBackLink, createTable2) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({false, {}});
    auto v2 = g.addNodeInBack({false, {}});
    g.addLink(v1, v0, 'a');
    g.addLink(v2,  v0, 'b');
    g.addLink(v0, v0, 'a');

    std::vector<std::map<char, std::vector<size_t>>> table = util::buildTableOfBackLink(g);
    std::vector<std::map<char, std::vector<size_t>>> res = {{ { 'a', {0, 1} }, {'b', {2}} }, {}, {}};
    ASSERT_EQ(table, res);
}

TEST(TestCreateTableOfBackLink, createTable3) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({false, {}});
    auto v2 = g.addNodeInBack({false, {}});
    g.addLink(v1, v0, 'a');
    g.addLink(v2,  v0, 'b');
    g.addLink(v0, v1, 'c');

    std::vector<std::map<char, std::vector<size_t>>> table = util::buildTableOfBackLink(g);
    std::vector<std::map<char, std::vector<size_t>>> res = {{ { 'a', {1} }, {'b', {2}} }, {{ {'c', {0}} }}, {}};
    ASSERT_EQ(table, res);
}

TEST(TestCreateTabelOfNotEquivalentVertex, oneEquivalenceXlassAClassOfNonterminal ) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({false, {}});
    auto v2 = g.addNodeInBack({false, {}});
    g.addLink(v1, v0, 'a');
    g.addLink(v2,  v0, 'b');
    g.addLink(v0, v0, 'a');
    std::vector<std::map<char, std::vector<size_t>>> tbl = util::buildTableOfBackLink(g);
    std::vector<std::vector<bool>> table = util::buildTableOfNotEquivalentVertex(
            {false, false, false}, tbl, g.getUniqueLinkData());
    std::vector<std::vector<bool>> res = { {false, false, false},
                                           {false, false, false},
                                           {false, false, false}};
    ASSERT_EQ(table, res);
}

TEST(TestCreateTabelOfNotEquivalentVertex, dijunction) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({false, {}});
    auto v2 = g.addNodeInBack({true, {}});
    g.addLink(v0, v1, 'a');
    g.addLink(v1, v2, 'b');
//    std::vector<std::vector<bool>> res = {{false, true, true},
//                                          {true, false, true},
//                                          {true, true, false}};
//    std::vector<std::map<char, std::vector<size_t>>> tbl = util::buildTableOfBackLink(g);
//    std::vector<std::vector<bool>> table = util::buildTableOfNotEquivalentVertex(
//            {false, false, true}, tbl, g.getUniqueLinkData());
    auto gg = util::minimizeDFSM(g);
    std::cout << util::graphToDOT(gg) << std::endl;
   // ASSERT_EQ(res, table);
}



TEST(TestCreateTabelOfNotEquivalentVertex, oneEquivalenceClassAClassOfTerminal ) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({false, {}});
    auto v2 = g.addNodeInBack({false, {}});
    g.addLink(v1, v0, 'a');
    g.addLink(v2,  v0, 'b');
    g.addLink(v0, v0, 'a');
    std::vector<std::map<char, std::vector<size_t>>> tbl = util::buildTableOfBackLink(g);
    std::vector<std::vector<bool>> table = util::buildTableOfNotEquivalentVertex(
            {true, true, true}, tbl, g.getUniqueLinkData());
    std::vector<std::vector<bool>> res = { {false, false, false},
                                           {false, false, false},
                                           {false, false, false}};
    ASSERT_EQ(table, res);
}

TEST(TestCreateTabelOfNotEquivalentVertex, twoEquivalentClasses) {
    Graph<std::pair<bool, std::set<size_t>>, char> g;
    auto v0 = g.addNodeInBack({false, {}});
    auto v1 = g.addNodeInBack({true, {}});
    auto v2 = g.addNodeInBack({false, {}});
    g.addLink(v1, v0, 'a');
    g.addLink(v2,  v0, 'b');
    g.addLink(v0, v0, 'a');
    std::vector<std::map<char, std::vector<size_t>>> tbl = util::buildTableOfBackLink(g);
    std::vector<std::vector<bool>> table = util::buildTableOfNotEquivalentVertex(
            {false, true, false}, tbl, g.getUniqueLinkData());
    std::vector<std::vector<bool>> res = { {false, true, false},
                                           {true, false, true},
                                           {false, true, false}};
    ASSERT_EQ(table, res);
}

TEST(TestCreateTabelOfNotEquivalentVertex, FiveEquivalentClasses) {
    Graph<std::pair<bool, std::set<size_t>>, char> graph;
    auto a = graph.addNodeInBack({false, {}});
    auto b = graph.addNodeInBack({false, {}});
    auto c = graph.addNodeInBack({false, {}});
    auto d = graph.addNodeInBack({false, {}});
    auto e = graph.addNodeInBack({false, {}});
    auto f = graph.addNodeInBack({true, {}});
    auto g = graph.addNodeInBack({true, {}});
    auto h = graph.addNodeInBack({false, {}});
    graph.addLink(a, b, '1');
    graph.addLink(b, a, '1');
    graph.addLink(a, h, '0');
    graph.addLink(b, h, '0');
    graph.addLink(h, c, '0');
    graph.addLink(h, c, '1');
    graph.addLink(c, e, '0');
    graph.addLink(c, f, '1');
    graph.addLink(e, f, '0');
    graph.addLink(e, g, '1');
    graph.addLink(g, f, '1');
    graph.addLink(g, g, '0');
    graph.addLink(f, f, '0');
    graph.addLink(f, f, '1');
    graph.addLink(d, e, '0');
    graph.addLink(d, f, '1');
    util::addDevilsVertex(graph);
    std::vector<std::map<char, std::vector<size_t>>> tbl = util::buildTableOfBackLink(graph);
    std::vector<std::vector<bool>> table = util::buildTableOfNotEquivalentVertex(
            {false, false, false, false, false, false, true, true, false}, tbl, graph.getUniqueLinkData());
   std::vector<std::vector<bool>> res = { { false, true, true, true, true, true, true, true, true },
                                          {true, false, false, true, true, true, true, true, true},
                                          {true, false, false, true, true, true, true, true, true},
                                          {true, true, true, false, false, true, true, true, true},
                                          {true, true, true, false, false, true, true, true, true},
                                          {true, true, true, true, true, false, true, true, true},
                                          {true, true, true, true, true, true, false, false, true},
                                          {true, true, true, true, true, true, false, false, true},
                                          {true, true, true, true, true, true, true, true, false}
                                        };

    ASSERT_EQ(table, res);

    std::cout << '1';

}

TEST(TestMinimizeDFSM, minimize) {
    Graph<std::pair<bool, std::set<size_t>>, char> graph;
    // auto devilVertex = graph.addNodeInBack({false, {}});
    auto a = graph.addNodeInBack({false, {}});
    auto b = graph.addNodeInBack({false, {}});
    auto c = graph.addNodeInBack({false, {}});
    auto d = graph.addNodeInBack({false, {}});
    auto e = graph.addNodeInBack({false, {}});
    auto f = graph.addNodeInBack({true, {}});
    auto g = graph.addNodeInBack({true, {}});
    auto h = graph.addNodeInBack({false, {}});
    graph.addLink(a, b, '1');
    graph.addLink(b, a, '1');
    graph.addLink(a, h, '0');
    graph.addLink(b, h, '0');
    graph.addLink(h, c, '0');
    graph.addLink(h, c, '1');
    graph.addLink(c, e, '0');
    graph.addLink(c, f, '1');
    graph.addLink(e, f, '0');
    graph.addLink(e, g, '1');
    graph.addLink(g, f, '1');
    graph.addLink(g, g, '0');
    graph.addLink(f, f, '0');
    graph.addLink(f, f, '1');
    graph.addLink(d, e, '0');
    graph.addLink(d, f, '1');
    auto mg = util::minimizeDFSM(graph);
    std::cout << util::graphToDOT(mg) << std::endl;
    std::cout << "util::graphToDOT(mg) << std::endl";
}