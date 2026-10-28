// Copyright 2026 Igor
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <utility>
#include "../LibStackOnMass/StackOnMass.h"

// Тест начального состояния
TEST(StackTest, InitialState) {
    StackOnMass<int> stack(5);
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
}

// Тест базовых операций push и pop
TEST(StackTest, BasicOperations) {
    StackOnMass<int> stack(5);

    stack.push(10);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    stack.push(30);
    EXPECT_EQ(stack.top(), 30);

    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.top(), 20);

    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);
    EXPECT_TRUE(stack.isEmpty());
}

// Тест работы до заполнения
TEST(StackTest, FullStack) {
    StackOnMass<int> stack(3);

    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_TRUE(stack.isFull());
    EXPECT_FALSE(stack.isEmpty());

    EXPECT_EQ(stack.top(), 3);
}

// Тест исключения при переполнении
TEST(StackTest, PushOnFullStack) {
    StackOnMass<int> stack(2);

    stack.push(1);
    stack.push(2);
    EXPECT_TRUE(stack.isFull());

    EXPECT_THROW(stack.push(3), std::logic_error);
}

// Тест исключения при чтении из пустого стека
TEST(StackTest, PopOnEmptyStack) {
    StackOnMass<int> stack(2);

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_THROW(stack.pop(), std::logic_error);
    EXPECT_THROW(stack.top(), std::logic_error);
}

// Тест конструктора копирования
TEST(StackTest, CopyConstructor) {
    StackOnMass<int> stack1(5);
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);

    StackOnMass<int> stack2(stack1);

    EXPECT_EQ(stack2.top(), 30);
    EXPECT_EQ(stack2.pop(), 30);
    EXPECT_EQ(stack2.top(), 20);

    // Проверяем, что оригинальный стек не изменился
    EXPECT_EQ(stack1.top(), 30);
}

// Тест move-конструктора
TEST(StackTest, MoveConstructor) {
    StackOnMass<int> stack1(5);
    stack1.push(10);
    stack1.push(20);

    StackOnMass<int> stack2(std::move(stack1));

    EXPECT_EQ(stack2.top(), 20);
    EXPECT_EQ(stack2.pop(), 20);
    EXPECT_EQ(stack2.top(), 10);
}

// Тест с типом std::string
TEST(StackTest, StringType) {
    StackOnMass<std::string> stack(3);

    stack.push("hello");
    stack.push("world");

    EXPECT_EQ(stack.top(), "world");
    EXPECT_EQ(stack.pop(), "world");
    EXPECT_EQ(stack.top(), "hello");
}

// Тест с типом double
TEST(StackTest, DoubleType) {
    StackOnMass<double> stack(3);

    stack.push(3.14);
    stack.push(2.71);

    EXPECT_DOUBLE_EQ(stack.top(), 2.71);
    EXPECT_DOUBLE_EQ(stack.pop(), 2.71);
    EXPECT_DOUBLE_EQ(stack.top(), 3.14);
}

// Тест последовательности операций
TEST(StackTest, MixedOperations) {
    StackOnMass<int> stack(5);

    stack.push(1);
    stack.push(2);
    EXPECT_EQ(stack.pop(), 2);

    stack.push(3);
    stack.push(4);
    EXPECT_EQ(stack.top(), 4);

    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_TRUE(stack.isEmpty());
}
