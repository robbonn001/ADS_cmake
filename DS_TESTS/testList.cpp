// Copyright 2026 Igor
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include "List.h"

// Тест начального состояния
TEST(ListTest, InitialState) {
    List<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
}

// Тест push_front и pop_front
TEST(ListTest, PushFrontAndPopFront) {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.pop_front(), 30);
    EXPECT_EQ(list.pop_front(), 20);
    EXPECT_EQ(list.pop_front(), 10);
    EXPECT_TRUE(list.isEmpty());
}

// Тест push_back и pop_back
TEST(ListTest, PushBackAndPopBack) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.pop_back(), 30);
    EXPECT_EQ(list.pop_back(), 20);
    EXPECT_EQ(list.pop_back(), 10);
    EXPECT_TRUE(list.isEmpty());
}

// Тест insert по индексу
TEST(ListTest, InsertByIndex) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);

    list.insert(20, 1);  // Вставка между 10 и 30

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.pop_front(), 10);
    EXPECT_EQ(list.pop_front(), 20);
    EXPECT_EQ(list.pop_front(), 30);

    // Вставка в начало и конец через insert
    list.push_back(50);
    list.insert(40, 1);

    list.insert(5, 0);
    list.insert(60, 3);

    EXPECT_EQ(list.pop_front(), 5);
    list.pop_front();  // 40 (если бы вставили, но мы проверим проще)
}

// Уточненный тест insert по индексу
TEST(ListTest, InsertByIndexDetailed) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    list.insert(2, 1);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.erase(0), 1);
    EXPECT_EQ(list.erase(0), 2);
    EXPECT_EQ(list.erase(0), 3);
}

// Тест insert по указателю на узел
TEST(ListTest, InsertByNode) {
    List<int> list;
    Node<int>* node1 = list.push_back(10);
    Node<int>* node2 = list.push_back(30);

    list.insert(node1, 20);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.pop_front(), 10);
    EXPECT_EQ(list.pop_front(), 20);
    EXPECT_EQ(list.pop_front(), 30);
}

// Тест исключений при insert
TEST(ListTest, InsertExceptions) {
    List<int> list;
    list.push_back(10);

    EXPECT_THROW(list.insert(20, 5), std::out_of_range);

    Node<int>* invalid_node = nullptr;
    EXPECT_THROW(list.insert(invalid_node, 20), std::invalid_argument);
}

// Тест pop на пустом списке
TEST(ListTest, PopEmptyListExceptions) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

// Тест erase
TEST(ListTest, Erase) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    EXPECT_EQ(list.erase(1), 20);  // Удаляем из середины
    EXPECT_EQ(list.size(), 3);

    EXPECT_EQ(list.erase(0), 10);  // Удаляем из начала
    EXPECT_EQ(list.size(), 2);

    EXPECT_EQ(list.erase(1), 40);  // Удаляем из конца (индекс 1 при размере 2)
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.pop_front(), 30);
    EXPECT_TRUE(list.isEmpty());
}

// Тест исключений при erase
TEST(ListTest, EraseExceptions) {
    List<int> list;
    EXPECT_THROW(list.erase(0), std::out_of_range);

    list.push_back(10);
    EXPECT_THROW(list.erase(1), std::out_of_range);
}

// Тест find
TEST(ListTest, Find) {
    List<std::string> list;
    list.push_back("apple");
    list.push_back("banana");
    list.push_back("cherry");

    Node<std::string>* found = list.find("banana");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->data_, "banana");

    Node<std::string>* not_found = list.find("grape");
    EXPECT_EQ(not_found, nullptr);
}

// Тест конструктора копирования
TEST(ListTest, CopyConstructor) {
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    List<int> list2(list1);

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.pop_front(), 10);
    EXPECT_EQ(list2.pop_front(), 20);

    // Проверяем, что оригинальный список не изменился
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list1.pop_front(), 10);
}

// Тест move-конструктора
TEST(ListTest, MoveConstructor) {
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    List<int> list2(std::move(list1));

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.pop_front(), 10);
    EXPECT_EQ(list2.pop_front(), 20);

    // Проверяем, что оригинальный список пуст
    EXPECT_TRUE(list1.isEmpty());
    EXPECT_EQ(list1.size(), 0);
}

// Тест списка из одного элемента
TEST(ListTest, SingleElementList) {
    List<int> list;
    list.push_back(42);

    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.pop_front(), 42);
    EXPECT_TRUE(list.isEmpty());

    list.push_front(99);
    EXPECT_EQ(list.pop_back(), 99);
    EXPECT_TRUE(list.isEmpty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
