// Copyright 2026 Igor
#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "DList.h"

// Базовый тест: проход по всему списку
TEST(DIteratorTest, BasicTraversal) {
  DList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  std::vector<int> result;
  for (auto it = list.begin(); it != list.end(); ++it) {
    result.push_back(*it);
  }

  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
  EXPECT_EQ(result[3], 4);
}

// Тест range-based for
TEST(DIteratorTest, RangeBasedFor) {
  DList<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  int sum = 0;
  for (int x : list) {
    sum += x;
  }
  EXPECT_EQ(sum, 60);
}

// Тест изменения элементов через итератор
TEST(DIteratorTest, ModificationViaDIterator) {
  DList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  for (auto it = list.begin(); it != list.end(); ++it) {
    *it *= 10;
  }

  auto it = list.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
}

// Тест константного итератора - нельзя изменять данные
TEST(DIteratorTest, ConstDIteratorCannotModify) {
  DList<int> list;
  list.push_back(1);
  list.push_back(2);

  const DList<int>& const_list = list;

  int i = 0;
  for (auto it = const_list.begin(); it != const_list.end(); ++it) {
    EXPECT_EQ(*it, ++i);
  }
}

// Тест cbegin/cend
TEST(DIteratorTest, CbeginCend) {
  DList<int> list;
  list.push_back(5);
  list.push_back(10);

  auto it = list.cbegin();
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(it, list.cend());
}

// Тест пустого списка
TEST(DIteratorTest, EmptyDList) {
  DList<int> list;
  EXPECT_EQ(list.begin(), list.end());
  EXPECT_EQ(list.cbegin(), list.cend());

  int count = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 0);
}

// Тест списка из одного элемента
TEST(DIteratorTest, SingleElement) {
  DList<int> list;
  list.push_back(42);

  auto it = list.begin();
  EXPECT_NE(it, list.end());
  EXPECT_EQ(*it, 42);
  ++it;
  EXPECT_EQ(it, list.end());
}

// Тест постфиксного инкремента
TEST(DIteratorTest, PostfixIncrement) {
  DList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it = list.begin();
  auto old_it = it++;

  EXPECT_EQ(*old_it, 1);  // old_it остался на первом элементе
  EXPECT_EQ(*it, 2);      // it перешел на второй
}

// Тест префиксного инкремента
TEST(DIteratorTest, PrefixIncrement) {
  DList<int> list;
  list.push_back(1);
  list.push_back(2);

  auto it = list.begin();
  auto& ref = ++it;  // Должен возвращать ссылку на себя

  EXPECT_EQ(&ref, &it);
  EXPECT_EQ(*it, 2);
}

// Тест operator->
TEST(DIteratorTest, ArrowOperator) {
  struct Point {
    int x;
    int y;
  };

  DList<Point> list;
  list.push_back({1, 2});
  list.push_back({3, 4});

  auto it = list.begin();
  EXPECT_EQ(it->x, 1);
  EXPECT_EQ(it->y, 2);

  it->x = 100;
  EXPECT_EQ(it->x, 100);
}

// Тест const-методов begin/end
TEST(DIteratorTest, ConstMemberFunctions) {
  DList<int> list;
  list.push_back(1);
  list.push_back(2);

  const DList<int>& cref = list;

  int sum = 0;
  for (auto it = cref.begin(); it != cref.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 3);
}

// Тест со строками
TEST(DIteratorTest, StringDList) {
  DList<std::string> list;
  list.push_back("hello");
  list.push_back("world");

  std::string result;
  for (const auto& s : list) {
    result += s + " ";
  }
  EXPECT_EQ(result, "hello world ");
}
