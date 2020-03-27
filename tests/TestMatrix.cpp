//
// Created by nrx on 13.03.2020.
//

#include "Matrix.h"
#include "gtest/gtest.h"

TEST(MatrixTest, MatrixTest) {
    Matrix<int> m(2, 2);
    ASSERT_EQ(m.at(0, 0), 0);
    ASSERT_EQ(m.at(0, 1), 0);
    ASSERT_EQ(m.at(1, 0), 0);
    ASSERT_EQ(m.at(1, 1), 0);
    m.at(0, 0) = 5;
    m.at(1, 1) = 6;
    ASSERT_EQ(m.at(0, 0), 5);
    ASSERT_EQ(m.at(1, 1), 6);
}