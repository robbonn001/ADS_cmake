// Copyright 2026 Igor
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <utility>

#include "../LibQueue/Queue.h"

// Тест начального состояния
TEST(QueueTest, InitialState) {
  Queue<int> q(5);
  EXPECT_EQ(q.count(), 0);
  EXPECT_EQ(q.size(), 5);
  EXPECT_TRUE(q.isEmpty());
  EXPECT_FALSE(q.isFull());
}

// Тест базовых операций push и pop
TEST(QueueTest, BasicOperations) {
  Queue<int> q(5);

  q.push(10);
  EXPECT_EQ(q.count(), 1);
  EXPECT_FALSE(q.isEmpty());
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 10);

  q.push(20);
  q.push(30);
  EXPECT_EQ(q.count(), 3);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 30);

  q.pop();
  EXPECT_EQ(q.count(), 2);
  EXPECT_EQ(q.front(), 20);

  q.pop();
  q.pop();
  EXPECT_EQ(q.count(), 0);
  EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, Push) {
  Queue<int> q(3);

  EXPECT_TRUE(q.isEmpty());
  q.push(10);
  EXPECT_EQ(q.count(), 1);
  EXPECT_FALSE(q.isEmpty());
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 10);

  q.push(20);
  q.push(30);
  EXPECT_EQ(q.count(), 3);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 30);
  EXPECT_TRUE(q.isFull());
}

TEST(QueueTest, Pop) {
  Queue<int> q(3);

  q.push(10);
  q.push(20);
  q.push(30);
  EXPECT_EQ(q.count(), 3);
  EXPECT_TRUE(q.isFull());

  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 30);

  q.pop();
  q.pop();
  q.pop();
  EXPECT_EQ(q.count(), 0);
  EXPECT_TRUE(q.isEmpty());
}

// Тест кольцевого переполнения
TEST(QueueTest, CircularWrapAround) {
  Queue<int> q(3);

  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_TRUE(q.isFull());

  q.pop();
  q.pop();
  EXPECT_EQ(q.count(), 1);
  EXPECT_EQ(q.front(), 3);

  q.push(4);
  q.push(5);
  EXPECT_TRUE(q.isFull());
  EXPECT_EQ(q.count(), 3);

  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 5);
  q.pop();

  EXPECT_TRUE(q.isEmpty());
}

// Тест исключений при работе с пустой очередью
TEST(QueueTest, EmptyQueueExceptions) {
  Queue<int> q(2);

  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
  EXPECT_THROW(q.pop(), std::out_of_range);
}

// Тест исключения при работе с полной очередью
TEST(QueueTest, FullQueueException) {
  Queue<int> q(2);

  q.push(1);
  q.push(2);
  EXPECT_TRUE(q.isFull());

  EXPECT_THROW(q.push(3), std::overflow_error);
}

// Тест с емкостью 1
TEST(QueueTest, sizeOne) {
  Queue<int> q(1);

  q.push(42);
  EXPECT_TRUE(q.isFull());
  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.back(), 42);

  q.pop();
  EXPECT_TRUE(q.isEmpty());

  q.push(99);
  EXPECT_EQ(q.front(), 99);
}

// Тест с типом std::string
TEST(QueueTest, StringType) {
  Queue<std::string> q(3);

  q.push("hello");
  q.push("world");

  EXPECT_EQ(q.front(), "hello");
  EXPECT_EQ(q.back(), "world");

  q.pop();
  EXPECT_EQ(q.front(), "world");
}

// Тест с типом double
TEST(QueueTest, DoubleType) {
  Queue<double> q(3);

  q.push(3.14);
  q.push(2.71);
  q.push(1.41);

  EXPECT_DOUBLE_EQ(q.front(), 3.14);
  EXPECT_DOUBLE_EQ(q.back(), 1.41);
}
