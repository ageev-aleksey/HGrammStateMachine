//
// Created by nrx on 21.03.2020.
//

#include "regex/util.h"
#include "gtest/gtest.h"
#include "regex/FSM.h"

TEST(TestConvertToRPN, RPN1) {
    std::string v = "x|y&z";
    ASSERT_EQ(util::convertToRPN(v), std::string("xyz&|"));
}

TEST(TestConvertToRPN, RPN2) {
    std::string v = "(x|y)&z";
    ASSERT_EQ(util::convertToRPN(v), std::string("xy|z&"));
}

TEST(TestConvertToRPN, RPN3) {
    std::string v = "x|(y&z)";
    ASSERT_EQ(util::convertToRPN(v), std::string("xyz&|"));
}

TEST(TestConvertToRPN, RPN4) {
    std::string v = "x&y*";
    ASSERT_EQ(util::convertToRPN(v), std::string("xy*&"));
}

TEST(TestConvertToRPN, RPN5) {
    std::string v = "(a|b)*&a&b&b";
    ASSERT_EQ(util::convertToRPN(v), std::string("ab|*a&b&b&"));
   // std::cout << util::convertToRPN(v) << std::endl;
    //a–(b+c*d)/e.
}


TEST(TestConvertToRPN, RPN6) {
    std::string v = "a|(b|c&d)&e";
    ASSERT_EQ(util::convertToRPN(v), std::string("abcd&|e&|"));
}

TEST(TestGraphFromRegex, ConcatenationTest) {
    Graph<Empty, char> g = util::graphFromRegex("ab&");
    std::cout << util::graphToDOT(g);
}

TEST(TestGraphFromRegex, KliniStarTest) {
    Graph<Empty, char> g = util::graphFromRegex("a*");
    std::cout << util::graphToDOT(g);
}

TEST(TestGraphFromRegex, DisjunctionTest) {
    Graph<Empty, char> g = util::graphFromRegex("ab|");
    std::cout << util::graphToDOT(g);
}

TEST(TestGraphFromRegex, mix) {
    Graph<Empty, char> g = util::graphFromRegex("ab|*");
    std::cout << util::graphToDOT(g);
}

TEST(TestGraphFromRegex, MixRgexOperation) {
    Graph<Empty, char> g = util::graphFromRegex(util::convertToRPN("(a|b)*&a&b&b"));
    std::cout << util::graphToDOT(g);
}

TEST(TestConvertNFSMtoDFSM, ConverterTest) {
    Graph<Empty, char> g = util::graphFromRegex(util::convertToRPN("(a|b)&c"));
    std::cout << util::graphToDOT(g);
    auto g2 = util::convertNFSMtoDFSM2(g);
    std::cout << util::graphToDOT(g2);
    std::cout << "!\n";
}

TEST(TestToGlueEpsilonTransmition, oneEpsilonLinkToGlue) {
    Graph<Empty, char> g;
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    g.addLink(v1, v2, 'a');
    g.addLink(v2, v1, util::EPSILON);
    std::set<size_t> v = util::toGlueEpsilonTransition({v2.getIndex()}, g);
    std::set result{v1.getIndex(), v2.getIndex()};
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, oneEpsilonLinkDontToGlue) {
    Graph<Empty, char> g;
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    g.addLink(v1, v2, 'a');
    g.addLink(v2, v1, util::EPSILON);
    std::set<size_t> v = util::toGlueEpsilonTransition({v1.getIndex()}, g);
    std::set result{v1.getIndex()};
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, AllLinksInFullGrpahIsEpsilonTransmition) {
    Graph<Empty, char> g;
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    auto v3 = g.addNodeInBack(Empty{});
    g.addLink(v1, v2, util::EPSILON);
    g.addLink(v2, v1, util::EPSILON);
    g.addLink(v2, v3, util::EPSILON);
    g.addLink(v3, v2, util::EPSILON);
    g.addLink(v1, v3, util::EPSILON);
    g.addLink(v3, v1, util::EPSILON);
    g.addLink(v1, v1, util::EPSILON);
    g.addLink(v2, v2, util::EPSILON);
    g.addLink(v3, v3, util::EPSILON);

    std::set<size_t> result{v1.getIndex(), v2.getIndex(), v3.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v1.getIndex()}, g);
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, GlueEpsiloneTransmitionStartedInOneVertex) {
    Graph<Empty, char> g;
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    auto v3 = g.addNodeInBack(Empty{});
    auto v4 = g.addNodeInBack(Empty{});
    auto v5 = g.addNodeInBack(Empty{});
    auto v6 = g.addNodeInBack(Empty{});
    auto v7 = g.addNodeInBack(Empty{});

    g.addLink(v1, v2, util::EPSILON);
    g.addLink(v2, v3, util::EPSILON);
    g.addLink(v2, v5, util::EPSILON);
    g.addLink(v3, v4, 'a');
    g.addLink(v4, v7, util::EPSILON);
    g.addLink(v5, v6, 'g');
    g.addLink(v6, v7, util::EPSILON);
    g.addLink(v6, v3, util::EPSILON);

    std::set<size_t> result{v1.getIndex(), v2.getIndex(), v3.getIndex(), v5.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v1.getIndex()}, g);
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, GlueEpsiloneTransmitionStartedInTwoVertex) {
    Graph<Empty, char> g;
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    auto v3 = g.addNodeInBack(Empty{});
    auto v4 = g.addNodeInBack(Empty{});
    auto v5 = g.addNodeInBack(Empty{});
    auto v6 = g.addNodeInBack(Empty{});
    auto v7 = g.addNodeInBack(Empty{});

    g.addLink(v1, v2, util::EPSILON);
    g.addLink(v2, v3, util::EPSILON);
    g.addLink(v2, v5, util::EPSILON);
    g.addLink(v3, v4, 'a');
    g.addLink(v4, v7, util::EPSILON);
    g.addLink(v5, v6, 'g');
    g.addLink(v6, v7, util::EPSILON);
    g.addLink(v6, v3, util::EPSILON);

    std::set<size_t> result{v1.getIndex(), v2.getIndex(), v3.getIndex(), v5.getIndex(), v6.getIndex(), v7.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v1.getIndex(), v6.getIndex()}, g);
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, GraphWithoutEpsilonTransmitions) {
    Graph<Empty, char> g;
    auto v0 = g.addNodeInBack(Empty{});
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});

    g.addLink(v0, v1, 'a');
    g.addLink(v1, v0, 'a');
    g.addLink(v1, v2, 'o');
    g.addLink(v2, v1, '0');
    g.addLink(v2, v0, '0');

    std::set<size_t> result{v0.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v0.getIndex()}, g);
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, GraphWithoutEpsilonTransmitions2) {
    Graph<Empty, char> g;
    auto v0 = g.addNodeInBack(Empty{});
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});

    g.addLink(v0, v1, 'a');
    g.addLink(v1, v0, 'a');
    g.addLink(v1, v2, 'o');
    g.addLink(v2, v1, '0');
    g.addLink(v2, v0, '0');

    std::set<size_t> result{v0.getIndex(), v2.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v0.getIndex(), v2.getIndex()}, g);
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, TwoStartedVertexButOneHaveAEpsiloneTransmition) {
    Graph<Empty, char> g;
    auto v0 = g.addNodeInBack(Empty{});
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});
    auto v3 = g.addNodeInBack(Empty{});

    g.addLink(v0, v1, 'a');
    g.addLink(v1, v0, util::EPSILON);
    g.addLink(v1, v2, 'o');
    g.addLink(v2, v1, '0');
    g.addLink(v2, v0, '0');
    g.addLink(v3, v2, '1');

    std::set<size_t> result{v0.getIndex(), v1.getIndex(), v3.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v1.getIndex(), v3.getIndex()}, g);
    ASSERT_EQ(v, result);
}

TEST(TestToGlueEpsilonTransmition, GraphWithoutLinks) {
    Graph<Empty, char> g;
    auto v0 = g.addNodeInBack(Empty{});
    auto v1 = g.addNodeInBack(Empty{});
    auto v2 = g.addNodeInBack(Empty{});

    std::set<size_t> result{v0.getIndex()};
    std::set<size_t> v = util::toGlueEpsilonTransition({v0.getIndex()}, g);
    ASSERT_EQ(v, result);
}