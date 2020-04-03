//
// Created by nrx on 03.04.2020.
//

#include "regex/util.h"
#include "gtest/gtest.h"

TEST(TestConvertRegexToFSM, oneSymbole) {
    Graph<Empty, char> g1 = util::graphFromRegex("a");
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);
    std::vector<std::map<char, size_t>> ok = { { {'a', 1} }, { {'a', -1} } };
    ASSERT_EQ(table, ok);
}

TEST(TestConvertRegexToFSM, conjuction) {
    Graph<Empty, char> g1 = util::graphFromRegex("ab&");
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);
    std::vector<std::map<char, size_t>> ok = { { {'a', 1}, {'b', -1}}, { {'a', -1}, {'b', 2} },  { {'a', -1}, {'b', -1} }};
    std::cout << util::graphToDOT(minFsm) << std::endl;
    ASSERT_EQ(table, ok);
}

TEST(TestConvertRegexToFSM, disjunction) {
    Graph<Empty, char> g1 = util::graphFromRegex("ab|");
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);
    std::vector<std::map<char, size_t>> ok = { { {'a', 1}, {'b', 1}}, { {'a', -1}, {'b', -1} } };
    ASSERT_EQ(table, ok);
}

TEST(TestConvertRegexToFSM, starOfKlini) {
    Graph<Empty, char> g1 = util::graphFromRegex("a*");
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);
    std::vector<std::map<char, size_t>> ok = { {{'a', 0}} };
    ASSERT_EQ(table, ok);
}

TEST(TestConvertRegexToFSM, combine1) {
    Graph<Empty, char> g1 = util::graphFromRegex(util::convertToRPN("(a|b)*"));
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);
    std::vector<std::map<char, size_t>> ok = { {{'a', 0}, {'b', 0}} };
    ASSERT_EQ(table, ok);
}

TEST(TestConvertRegexToFSM, combine2) {
    Graph<Empty, char> g1 = util::graphFromRegex(util::convertToRPN("(a|b)&(a|b)*"));
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);
    std::cout << util::graphToDOT(minFsm) << std::endl;
    std::vector<std::map<char, size_t>> ok = { {{'a', 1}, {'b', 1}}, {{'a', 1}, {'b', 1}} };
    ASSERT_EQ(table, ok);
}


TEST(TestConvertRegexToFSM, combine3) {
    Graph<Empty, char> g1 = util::graphFromRegex(util::convertToRPN("0&(0|1|2|3|4|5|6|7)&(0|1|2|3|4|5|6|7)*"));
    Graph<std::pair<bool, std::set<size_t>>,char> dfsm = util::convertNFSMtoDFSM2(g1);
    Graph<std::pair<bool, std::set<size_t>>, char> minFsm = util::minimizeDFSM(dfsm);
    std::vector<std::map<char, size_t>> table = util::buildConversionTable(minFsm);

    std::vector<std::map<char, size_t>> ok = { {{'a', 1}, {'b', 1}}, {{'a', 1}, {'b', 1}} };
    ASSERT_EQ(table, ok);
}