// Copyright 2026 Igor
#include <gtest/gtest.h>
#include <string>
#include "../Algorithms/brackets.cpp"

TEST(TestBracket, checkTrue) {
    std::string expression = "{(())()[()()]}";
    EXPECT_TRUE(checkBreackets(expression));
}

TEST(TestBracket, checkFalse) {
    std::string expression = "{(())([()()]}";
    EXPECT_FALSE(checkBreackets(expression));
    expression = "]{(())()[()()}";
    EXPECT_FALSE(checkBreackets(expression));
    expression = "{(())()[()()}[";
    EXPECT_FALSE(checkBreackets(expression));
}
