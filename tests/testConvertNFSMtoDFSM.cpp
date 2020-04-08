//
// Created by nrx on 28.03.2020.
//

#include "regex/util.h"
#include "gtest/gtest.h"


TEST(TestConvertNFSMtoDFSM, removeOneEpsilonTramsmition) {
    Graph<Empty, char> g;
    auto v0 = g.addNodeInBack(Empty{});
    auto v1 = g.addNodeInBack(Empty{});
    g.addLink(v0, v1, 'a');
    g.addLink(v1, v0, util::EPSILON);
    auto dfsm = util::convertNFSMtoDFSM2(g);
    auto dfsmTable = util::buildConversionTable(dfsm);
    std::vector<std::map<char, size_t>> rightTable = { { {'a', 1} } , { {'a', 1} } };
    ASSERT_EQ(dfsmTable, rightTable);
}

TEST(TestConvertNFSMtoDFSM, ConvertStarOfKlini) {
    Graph<Empty, char> g;
    auto v0 = g.addNodeInBack(Empty{});
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    auto v3 = g.addNodeInBack(Empty{});
    auto v4 = g.addNodeInBack(Empty{});
    g.addLink(v0, v1, util::EPSILON);
    g.addLink(v0, v3, util::EPSILON);
    g.addLink(v1, v2, 'a');
    g.addLink(v2, v3, util::EPSILON);
    g.addLink(v2, v1, util::EPSILON);
    g.addLink(v3, v4, 'b');
    auto dfsm = util::convertNFSMtoDFSM2(g);
    auto dfsmTable = util::buildConversionTable(dfsm);
    std::vector<std::map<char, size_t>> rightTable = { { {'a', 1}, {'b', 2} },
                                                       { {'a', 1}, {'b', 2} },
                                                       { {'a', -1}, {'b', -1}} };
    ASSERT_EQ(dfsmTable, rightTable);
}

TEST(TestConvertNFSMtoDFSM, Regex) {
  Graph<Empty, char> g = util::graphFromRegex(util::convertToRPN("(a&(b|c))*&c"));
  auto dfsm = util::convertNFSMtoDFSM2(g);
  auto dfsmTable = util::buildConversionTable(dfsm);
  std::vector<std::map<char, size_t>> rightTable = { { {'a', 1},  {'b', -1}, {'c', 2} },
                                                     { {'a', -1},  {'b', 3}, {'c', 4} },
                                                     { {'a', -1}, {'b', -1}, {'c', -1} },
                                                     {  {'a', 1}, {'b', -1},  {'c', 2} },
                                                     {  {'a', 1}, {'b', -1},  {'c', 2} }};
    ASSERT_EQ(dfsmTable, rightTable);

}