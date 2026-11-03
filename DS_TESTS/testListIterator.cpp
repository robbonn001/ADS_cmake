// Copyright 2026 Igor
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <vector>
#include "List.h"

// Базовый тест: проход по всему списку
TEST(IteratorTest, BasicTraversal) {
    List<int> list;
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
TEST(IteratorTest, RangeBasedFor) {
    List<int> list;
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
TEST(IteratorTest, ModificationViaIterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    for (auto it = list.begin(); it != list.end(); ++it) {
        *it *= 10;
    }

    auto it = list.begin();
    EXPECT_EQ(*it, 10); ++it;
    EXPECT_EQ(*it, 20); ++it;
    EXPECT_EQ(*it, 30);
}

// Тест константного итератора - нельзя изменять данные
TEST(IteratorTest, ConstIteratorCannotModify) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    const List<int>& const_list = list;

    // Проверяем, что итератор действительно константный
    auto it = const_list.begin();
    static_assert(std::is_same<decltype(*it), const int&>::value,
        "Const iterator should return const reference");

    EXPECT_EQ(*it, 1);
}

// Тест cbegin/cend
TEST(IteratorTest, CbeginCend) {
    List<int> list;
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
TEST(IteratorTest, EmptyList) {
    List<int> list;
    EXPECT_EQ(list.begin(), list.end());
    EXPECT_EQ(list.cbegin(), list.cend());

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 0);
}

// Тест списка из одного элемента
TEST(IteratorTest, SingleElement) {
    List<int> list;
    list.push_back(42);

    auto it = list.begin();
    EXPECT_NE(it, list.end());
    EXPECT_EQ(*it, 42);
    ++it;
    EXPECT_EQ(it, list.end());
}

// Тест постфиксного инкремента
TEST(IteratorTest, PostfixIncrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    auto old_it = it++;

    EXPECT_EQ(*old_it, 1);  // old_it остался на первом элементе
    EXPECT_EQ(*it, 2);      // it перешел на второй
}

// Тест префиксного инкремента
TEST(IteratorTest, PrefixIncrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    auto& ref = ++it;  // Должен возвращать ссылку на себя

    EXPECT_EQ(&ref, &it);
    EXPECT_EQ(*it, 2);
}

// Тест operator->
TEST(IteratorTest, ArrowOperator) {
    struct Point {
        int x;
        int y;
    };

    List<Point> list;
    list.push_back({ 1, 2 });
    list.push_back({ 3, 4 });

    auto it = list.begin();
    EXPECT_EQ(it->x, 1);
    EXPECT_EQ(it->y, 2);

    it->x = 100;
    EXPECT_EQ(it->x, 100);
}

// Тест const-методов begin/end
TEST(IteratorTest, ConstMemberFunctions) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    const List<int>& cref = list;

    int sum = 0;
    for (auto it = cref.begin(); it != cref.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 3);
}

// Тест со строками
TEST(IteratorTest, StringList) {
    List<std::string> list;
    list.push_back("hello");
    list.push_back("world");

    std::string result;
    for (const auto& s : list) {
        result += s + " ";
    }
    EXPECT_EQ(result, "hello world ");
}
