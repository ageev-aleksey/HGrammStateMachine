//
// Created by nrx on 26.03.2020.
//

#include "regex/util.h"
#include "regex/FSM.h"
#include "gtest/gtest.h"

using FSMe = FSM<Empty>;

TEST(TestFSM, TestGetAlphabet) {
    Graph<FSMe::Node, char> g;
    auto n1 = g.addNodeInFront(FSMe::Node());
    auto n2 = g.addNodeInFront(FSMe::Node());
    auto n3 = g.addNodeInFront(FSMe::Node());
    g.addLink(n1, n2, 'a');
    g.addLink(n1, n2, 'b');
    g.addLink(n1, n2, 'e');
    g.addLink(n1, n2, 'c');
    g.addLink(n2, n3, 'd');
    g.addLink(n2, n3, 'e');
    g.addLink(n3, n1, 'e');
    FSMe fsm(g);
    auto a = fsm.getAlphabet();
    std::unordered_set<char> alphabet = {'a', 'b', 'c', 'd', 'e'};
    for(const auto &el : a) {
        ASSERT_TRUE(alphabet.find(el) != alphabet.end());
    }
}


TEST(TestFSM, TestGetLinks) {
    Graph<FSMe::Node, char> g;
    auto n0 = g.addNodeInBack(FSMe::Node());
    auto n1 = g.addNodeInBack(FSMe::Node());
    auto n2 = g.addNodeInBack(FSMe::Node());
    g.addLink(n0, n1, 'a');
    g.addLink(n0, n1, 'b');
    g.addLink(n0, n1, 'e');
    g.addLink(n0, n1, 'c');
    g.addLink(n1, n2, 'd');
    g.addLink(n1, n2, 'e');
    g.addLink(n2, n0, 'e');
    FSMe fsm(g);
    auto l = fsm.getLinks();
    std::unordered_set<FSMe::Link> links = {{0, 1, 'a'}, {0, 1, 'b'}, {0, 1, 'c'}, {0, 1, 'e'},
                                            {1, 2, 'd'}, {1, 2, 'e'}, {2, 0, 'e'}};

    for(const auto &el : l) {
        //ASSERT_TRUE(links.find(el) != links.end());
        if(links.find(el) == links.end()) {
            std::cout << "--" << "not found: " << "("<< el.firstNode << "; " << el.secondNode
            << "; " << el.symbol << ")" << std::endl;
            ASSERT_FALSE(true);
        }
    }

}

TEST(TestFSM, TestGetNodeCount) {
    Graph<FSMe::Node, char> g;
    auto n0 = g.addNodeInBack(FSMe::Node());
    auto n1 = g.addNodeInBack(FSMe::Node());
    auto n2 = g.addNodeInBack(FSMe::Node());
    g.addLink(n0, n1, 'a');
    g.addLink(n0, n1, 'b');
    g.addLink(n0, n1, 'e');
    g.addLink(n0, n1, 'c');
    g.addLink(n1, n2, 'd');
    g.addLink(n1, n2, 'e');
    g.addLink(n2, n0, 'e');
    FSMe fsm(g);
    ASSERT_EQ(fsm.nodesCount(), 3);
}


