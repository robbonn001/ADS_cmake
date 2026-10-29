// Copyright 2026 Igor
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include "../LibMultiStack/MultiStack.h"

TEST(MultiStackTest, ConstructorTest) {
    MultiStack<int> multistack(10,3);
  EXPECT_TRUE(multistack.isEmpty());
}

TEST(MultiStackTest, PushTest) {
  MultiStack<int> multistack(10, 3);
    multistack.push(0, 1);
    multistack.push(0, 2);
    multistack.push(1, 5);
    multistack.push(1, 4);
    multistack.push(1, 3);
    multistack.push(2, 7);
    multistack.push(2, 8);
    EXPECT_EQ(multistack.top(0), 2);
    EXPECT_EQ(multistack.top(1), 3);
    EXPECT_EQ(multistack.top(2), 8);
}

TEST(MultiStackTest, PopTest) {
  MultiStack<int> multistack(10, 3);
  multistack.push(0, 1);
  multistack.push(0, 2);
  multistack.push(1, 5);
  multistack.push(1, 4);
  multistack.push(1, 3);
  multistack.push(2, 7);
  multistack.push(2, 8);
  multistack.pop(2);
  multistack.pop(1);
  multistack.pop(0);
  EXPECT_EQ(multistack.top(0), 1);
  EXPECT_EQ(multistack.top(1), 4);
  EXPECT_EQ(multistack.top(2), 7);
}

TEST(MultiStackTest, PushExceptionTest) {
  MultiStack<int> multistack(10, 3);
  multistack.push(0, 1);
  multistack.push(0, 2);
  multistack.push(0, 3);
  EXPECT_TRUE(multistack.isFullSector(0));
  EXPECT_THROW(multistack.push(0, 4), std::out_of_range);

}

TEST(MultiStackTest, PopExceptionTest) {
  MultiStack<int> multistack(10, 3);
  multistack.push(0, 1);
  multistack.pop(0);
  EXPECT_TRUE(multistack.isEmptySector(0));
  EXPECT_THROW(multistack.pop(0), std::out_of_range);
}

TEST(MultiStackTest, TopExceptionTest) {
  MultiStack<int> multistack(10, 3);
  EXPECT_THROW(multistack.top(0), std::out_of_range);
}

TEST(MultiStackTest, IsEmptyTest) {
  MultiStack<int> multistack(10, 3);
  EXPECT_TRUE(multistack.isEmpty());
}

TEST(MultiStackTest, IsFullTest) {
  MultiStack<int> multistack(10, 3);
  multistack.push(0, 1);
  multistack.push(0, 1);
  multistack.push(0, 1);

  multistack.push(1, 1);
  multistack.push(1, 1);
  multistack.push(1, 1);

  multistack.push(2, 1);
  multistack.push(2, 1);
  multistack.push(2, 1);
  multistack.push(2, 1);
  EXPECT_TRUE(multistack.isFull());
}
