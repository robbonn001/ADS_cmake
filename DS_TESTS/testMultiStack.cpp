// Copyright 2026 Igor
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <utility>

#include "../LibMultiStack/MultiStack.h"

// Тест начального состояния
TEST(MultiStackTest, InitialState) {
  MultiStack<int> stack(10, 3);

  EXPECT_TRUE(stack.isEmpty());
  EXPECT_FALSE(stack.isFull());

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_TRUE(stack.isEmptySector(i));
    EXPECT_FALSE(stack.isFullSector(i));
  }
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

// Тест базовых операций push и pop
TEST(MultiStackTest, BasicPushPop) {
  MultiStack<int> stack(10, 3);

  stack.push(0, 10);
  stack.push(1, 20);
  stack.push(2, 30);

  EXPECT_EQ(stack.top(0), 10);
  EXPECT_EQ(stack.top(1), 20);
  EXPECT_EQ(stack.top(2), 30);

  EXPECT_EQ(stack.pop(0), 10);
  EXPECT_EQ(stack.pop(1), 20);
  EXPECT_EQ(stack.pop(2), 30);

  EXPECT_TRUE(stack.isEmpty());
}

// Тест заполнения одного сектора
TEST(MultiStackTest, FillOneSector) {
  MultiStack<int> stack(10, 3);

  // Заполняем первый сектор (размер 3)
  stack.push(0, 1);
  stack.push(0, 2);
  stack.push(0, 3);

  EXPECT_TRUE(stack.isFullSector(0));
  EXPECT_FALSE(stack.isFullSector(1));
  EXPECT_FALSE(stack.isFullSector(2));

  EXPECT_EQ(stack.top(0), 3);
  EXPECT_EQ(stack.pop(0), 3);
  EXPECT_EQ(stack.top(0), 2);
}

// Тест repack при вставке в заполненный сектор
TEST(MultiStackTest, RepackOnFullSector) {
  MultiStack<int> stack(10, 3);

  // Заполняем секторы: 1-й=1 эл, 2-й=3 эл, 3-й=2 эл
  stack.push(0, 1);
  stack.push(1, 2);
  stack.push(1, 3);
  stack.push(1, 4);
  stack.push(2, 5);
  stack.push(2, 6);

  // 2-й сектор заполнен (размер 3)
  EXPECT_TRUE(stack.isFullSector(1));

  // Вставляем в заполненный 2-й сектор - должен сработать repack
  stack.push(1, 8);

  // После repack размеры: 2, 5, 3
  // Проверяем, что все элементы на месте
  EXPECT_EQ(stack.pop(0), 1);
  EXPECT_TRUE(stack.isEmptySector(0));

  EXPECT_EQ(stack.pop(1), 8);
  EXPECT_EQ(stack.pop(1), 4);
  EXPECT_EQ(stack.pop(1), 3);
  EXPECT_EQ(stack.pop(1), 2);
  EXPECT_TRUE(stack.isEmptySector(1));

  EXPECT_EQ(stack.pop(2), 6);
  EXPECT_EQ(stack.pop(2), 5);
  EXPECT_TRUE(stack.isEmptySector(2));
}

// Тест полного заполнения стека
TEST(MultiStackTest, FullStack) {
  MultiStack<int> stack(10, 3);

  // Заполняем весь стек
  for (int i = 0; i < 10; ++i) {
    stack.push(i % 3, i);
  }

  EXPECT_TRUE(stack.isFull());

  // Проверяем, что все элементы на месте
  for (int i = 0; i < 3; ++i) {
    EXPECT_TRUE(stack.isFullSector(i));
  }
}

// Тест исключений при работе с пустым сектором
TEST(MultiStackTest, EmptySectorExceptions) {
  MultiStack<int> stack(10, 3);

  EXPECT_THROW(stack.pop(0), std::logic_error);
  EXPECT_THROW(stack.top(0), std::logic_error);
}

// Тест исключений при работе с заполненным сектором
TEST(MultiStackTest, FullSectorException) {
  MultiStack<int> stack(3, 3);

  // Заполняем все секторы
  stack.push(0, 1);
  stack.push(1, 2);
  stack.push(2, 3);

  // Все секторы заполнены
  EXPECT_TRUE(stack.isFull());

  // Попытка вставки должна вызвать repack, но если repack невозможен
  // (все секторы заполнены и нет места), должно быть исключение
  EXPECT_THROW(stack.push(0, 4), std::overflow_error);
}

// Тест с типом std::string
TEST(MultiStackTest, StringType) {
  MultiStack<std::string> stack(10, 3);

  stack.push(0, "hello");
  stack.push(1, "world");
  stack.push(2, "test");

  EXPECT_EQ(stack.top(0), "hello");
  EXPECT_EQ(stack.top(1), "world");
  EXPECT_EQ(stack.top(2), "test");
}

// Тест множественных repack
TEST(MultiStackTest, MultipleRepacks) {
  MultiStack<int> stack(10, 3);

  // Заполняем первый сектор
  stack.push(0, 1);
  stack.push(0, 2);
  stack.push(0, 3);

  // Вставляем в заполненный 1-й сектор - repack #1
  stack.push(0, 4);

  // Снова заполняем 1-й сектор
  stack.push(0, 5);
  stack.push(0, 6);

  // Вставляем в заполненный 1-й сектор - repack #2
  stack.push(0, 7);

  // Проверяем, что все элементы на месте
  EXPECT_EQ(stack.pop(0), 7);
  EXPECT_EQ(stack.pop(0), 6);
  EXPECT_EQ(stack.pop(0), 5);
  EXPECT_EQ(stack.pop(0), 4);
  EXPECT_EQ(stack.pop(0), 3);
  EXPECT_EQ(stack.pop(0), 2);
  EXPECT_EQ(stack.pop(0), 1);
  EXPECT_TRUE(stack.isEmptySector(0));
}

// Тест граничного случая: 1 сектор
TEST(MultiStackTest, SingleSector) {
  MultiStack<int> stack(5, 1);

  stack.push(0, 10);
  stack.push(0, 20);
  stack.push(0, 30);

  EXPECT_EQ(stack.top(0), 30);
  EXPECT_EQ(stack.pop(0), 30);
  EXPECT_EQ(stack.pop(0), 20);
  EXPECT_EQ(stack.pop(0), 10);
  EXPECT_TRUE(stack.isEmpty());
}

// Тест LIFO порядка в каждом секторе
TEST(MultiStackTest, LIFOOrder) {
  MultiStack<int> stack(10, 3);

  stack.push(0, 1);
  stack.push(0, 2);
  stack.push(0, 3);

  EXPECT_EQ(stack.pop(0), 3);
  EXPECT_EQ(stack.pop(0), 2);
  EXPECT_EQ(stack.pop(0), 1);
}

// Тест независимости секторов
TEST(MultiStackTest, SectorIndependence) {
  MultiStack<int> stack(10, 3);

  stack.push(0, 10);
  stack.push(1, 20);
  stack.push(2, 30);

  // Изменяем один сектор
  EXPECT_EQ(stack.pop(1), 20);

  // Другие секторы не изменились
  EXPECT_EQ(stack.top(0), 10);
  EXPECT_EQ(stack.top(2), 30);
}

// Тест repack с остатком
TEST(MultiStackTest, RepackWithRemainder) {
  MultiStack<int> stack(11, 3);  // 11 не делится на 3

  // Заполняем: 1-й=1, 2-й=3, 3-й=2
  stack.push(0, 1);
  stack.push(1, 2);
  stack.push(1, 3);
  stack.push(1, 4);
  stack.push(2, 5);
  stack.push(2, 6);

  // Вставляем в 2-й сектор - repack
  // extraSpace = 11 - 7 = 4
  // extraSpacePerStack = 4/3 = 1
  // remainder = 4%3 = 1 (отходит 2-му сектору)
  stack.push(1, 7);

  // Проверяем, что все элементы на месте
  EXPECT_EQ(stack.pop(0), 1);
  EXPECT_EQ(stack.pop(1), 7);
  EXPECT_EQ(stack.pop(1), 4);
  EXPECT_EQ(stack.pop(1), 3);
  EXPECT_EQ(stack.pop(1), 2);
  EXPECT_EQ(stack.pop(2), 6);
  EXPECT_EQ(stack.pop(2), 5);
}

// ====== Тесты конструкторов ======

// Тест конструктора с параметрами: распределение памяти
TEST(MultiStackConstructorsTest, ConstructorDistribution) {
  // Размер 10, 3 подстека -> размеры 3, 3, 4 (лишка отходит последнему)
  MultiStack<int> stack(10, 3);

  // Заполняем первые два сектора полностью
  stack.push(0, 1);
  stack.push(0, 2);
  stack.push(0, 3);
  EXPECT_TRUE(stack.isFullSector(0));

  stack.push(1, 4);
  stack.push(1, 5);
  stack.push(1, 6);
  EXPECT_TRUE(stack.isFullSector(1));

  // Третий сектор должен иметь размер 4
  stack.push(2, 7);
  stack.push(2, 8);
  stack.push(2, 9);
  EXPECT_FALSE(stack.isFullSector(2));

  stack.push(2, 10);
  EXPECT_TRUE(stack.isFullSector(2));
  EXPECT_TRUE(stack.isFull());
}

// Тест конструктора с параметрами: размер делится без остатка
TEST(MultiStackConstructorsTest, ConstructorEvenDistribution) {
  // Размер 12, 3 подстека -> размеры 4, 4, 4
  MultiStack<int> stack(12, 3);

  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      stack.push(i, static_cast<int>(i * 10 + j));
    }
    EXPECT_TRUE(stack.isFullSector(i));
  }
  EXPECT_TRUE(stack.isFull());
}

// Тест конструктора с одним сектором
TEST(MultiStackConstructorsTest, ConstructorSingleSector) {
  MultiStack<int> stack(5, 1);

  for (int i = 0; i < 5; ++i) {
    stack.push(0, i);
  }
  EXPECT_TRUE(stack.isFull());

  for (int i = 4; i >= 0; --i) {
    EXPECT_EQ(stack.pop(0), i);
  }
  EXPECT_TRUE(stack.isEmpty());
}

// Тест конструктора с большим количеством секторов
TEST(MultiStackConstructorsTest, ConstructorManySectors) {
  MultiStack<int> stack(100, 10);

  // Каждый сектор должен иметь размер 10
  for (size_t i = 0; i < 10; ++i) {
    for (size_t j = 0; j < 10; ++j) {
      stack.push(i, static_cast<int>(i * 10 + j));
    }
    EXPECT_TRUE(stack.isFullSector(i));
  }
  EXPECT_TRUE(stack.isFull());
}

// ====== Тесты конструктора копирования ======

// Тест базового конструктора копирования
TEST(MultiStackCopyTest, CopyConstructor) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(0, 2);
  stack1.push(1, 3);
  stack1.push(2, 4);
  stack1.push(2, 5);

  MultiStack<int> stack2(stack1);

  // Проверяем, что данные скопированы
  EXPECT_EQ(stack2.top(0), 2);
  EXPECT_EQ(stack2.pop(0), 2);
  EXPECT_EQ(stack2.top(0), 1);

  EXPECT_EQ(stack2.top(1), 3);
  EXPECT_EQ(stack2.pop(1), 3);
  EXPECT_TRUE(stack2.isEmptySector(1));

  EXPECT_EQ(stack2.top(2), 5);
  EXPECT_EQ(stack2.pop(2), 5);
  EXPECT_EQ(stack2.top(2), 4);
}

// Тест независимости объектов после копирования
TEST(MultiStackCopyTest, CopyConstructorIndependence) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);

  MultiStack<int> stack2(stack1);

  // Изменяем stack2
  stack2.push(0, 100);
  stack2.pop(1);

  // stack1 не должен измениться
  EXPECT_EQ(stack1.top(0), 1);
  EXPECT_EQ(stack1.top(1), 2);
  EXPECT_FALSE(stack1.isEmptySector(1));
}

// Тест копирования пустого стека
TEST(MultiStackCopyTest, CopyConstructorEmpty) {
  MultiStack<int> stack1(10, 3);
  MultiStack<int> stack2(stack1);

  EXPECT_TRUE(stack2.isEmpty());
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_TRUE(stack2.isEmptySector(i));
  }
}

// Тест копирования полностью заполненного стека
TEST(MultiStackCopyTest, CopyConstructorFull) {
  MultiStack<int> stack1(9, 3);
  for (int i = 0; i < 9; ++i) {
    stack1.push(i % 3, i);
  }
  EXPECT_TRUE(stack1.isFull());

  MultiStack<int> stack2(stack1);
  EXPECT_TRUE(stack2.isFull());

  // Проверяем, что данные корректно скопированы
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_TRUE(stack2.isFullSector(i));
  }
}

// Тест копирования со строками
TEST(MultiStackCopyTest, CopyConstructorStrings) {
  MultiStack<std::string> stack1(10, 2);
  stack1.push(0, "hello");
  stack1.push(0, "world");
  stack1.push(1, "test");

  MultiStack<std::string> stack2(stack1);

  EXPECT_EQ(stack2.top(0), "world");
  EXPECT_EQ(stack2.pop(0), "world");
  EXPECT_EQ(stack2.top(0), "hello");
  EXPECT_EQ(stack2.top(1), "test");
}

// ====== Тесты move-конструктора ======

// Тест базового move-конструктора
TEST(MultiStackMoveTest, MoveConstructor) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);
  stack1.push(2, 3);

  MultiStack<int> stack2(std::move(stack1));

  // stack2 должен содержать все данные
  EXPECT_EQ(stack2.top(0), 1);
  EXPECT_EQ(stack2.top(1), 2);
  EXPECT_EQ(stack2.top(2), 3);

  // stack1 должен быть в валидном пустом состоянии
  EXPECT_TRUE(stack1.isEmpty());
  EXPECT_EQ(stack1.isEmpty(), stack1.isFull());
}

// ====== Тесты copy assignment ======

// Тест базового copy assignment
TEST(MultiStackCopyAssignTest, CopyAssignment) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);
  stack1.push(2, 3);

  MultiStack<int> stack2(10, 3);
  stack2.push(0, 100);
  stack2.push(1, 200);

  stack2 = stack1;

  // stack2 должен содержать данные stack1
  EXPECT_EQ(stack2.top(0), 1);
  EXPECT_EQ(stack2.top(1), 2);
  EXPECT_EQ(stack2.top(2), 3);
  EXPECT_FALSE(stack2.isEmptySector(0));
}

// Тест независимости после copy assignment
TEST(MultiStackCopyAssignTest, CopyAssignmentIndependence) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);

  MultiStack<int> stack2(10, 3);
  stack2 = stack1;

  // Изменяем stack2
  stack2.push(0, 100);
  stack2.pop(0);

  // stack1 не изменился
  EXPECT_EQ(stack1.top(0), 1);
}

// Тест самоприсваивания
TEST(MultiStackCopyAssignTest, CopyAssignmentSelfAssign) {
  MultiStack<int> stack(10, 3);
  stack.push(0, 1);
  stack.push(1, 2);
  stack.push(2, 3);

  stack = stack;  // Самоприсваивание

  // Данные не должны измениться
  EXPECT_EQ(stack.top(0), 1);
  EXPECT_EQ(stack.top(1), 2);
  EXPECT_EQ(stack.top(2), 3);
}

// Тест присваивания пустого стека в заполненный
TEST(MultiStackCopyAssignTest, CopyAssignmentEmptyToFull) {
  MultiStack<int> stack1(10, 3);
  MultiStack<int> stack2(10, 3);
  stack2.push(0, 1);
  stack2.push(1, 2);

  stack2 = stack1;

  EXPECT_TRUE(stack2.isEmpty());
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_TRUE(stack2.isEmptySector(i));
  }
}

// Тест присваивания заполненного стека в пустой
TEST(MultiStackCopyAssignTest, CopyAssignmentFullToEmpty) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);

  MultiStack<int> stack2(10, 3);
  stack2 = stack1;

  EXPECT_EQ(stack2.top(0), 1);
  EXPECT_EQ(stack2.top(1), 2);
  EXPECT_FALSE(stack2.isEmptySector(0));
  EXPECT_FALSE(stack2.isEmptySector(1));
  EXPECT_TRUE(stack2.isEmptySector(2));
}

// ====== Тесты move assignment ======

// Тест базового move assignment
TEST(MultiStackMoveAssignTest, MoveAssignment) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);
  stack1.push(2, 3);

  MultiStack<int> stack2(10, 3);
  stack2.push(0, 100);

  stack2 = std::move(stack1);

  // stack2 должен содержать данные stack1
  EXPECT_EQ(stack2.top(0), 1);
  EXPECT_EQ(stack2.top(1), 2);
  EXPECT_EQ(stack2.top(2), 3);

  // stack1 должен быть пуст
  EXPECT_TRUE(stack1.isEmpty());
}

// Тест самоприсваивания через move
TEST(MultiStackMoveAssignTest, MoveAssignmentSelfAssign) {
  MultiStack<int> stack(10, 3);
  stack.push(0, 1);
  stack.push(1, 2);

  stack = std::move(stack);  // Самоприсваивание

  // Данные не должны измениться (или стек должен остаться в валидном состоянии)
  EXPECT_FALSE(stack.isEmpty());
}

// Тест move assignment с освобождением ресурсов
TEST(MultiStackMoveAssignTest, MoveAssignmentResourceCleanup) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);

  MultiStack<int> stack2(10, 3);
  stack2.push(0, 100);
  stack2.push(0, 200);
  stack2.push(1, 300);

  // stack2 имел свои данные, которые должны быть освобождены
  stack2 = std::move(stack1);

  // stack2 теперь содержит данные stack1
  EXPECT_EQ(stack2.top(0), 1);
  EXPECT_EQ(stack2.top(1), 2);

  // stack1 пуст
  EXPECT_TRUE(stack1.isEmpty());
}

// ====== Тесты цепочки присваиваний ======

TEST(MultiStackAssignTest, ChainedAssignment) {
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);

  MultiStack<int> stack2(10, 3);
  MultiStack<int> stack3(10, 3);

  stack3 = stack2 = stack1;

  EXPECT_EQ(stack2.top(0), 1);
  EXPECT_EQ(stack3.top(0), 1);
}

// ====== Тесты Rule of Five ======

TEST(MultiStackRuleOfFiveTest, AllOperations) {
  // Конструктор
  MultiStack<int> stack1(10, 3);
  stack1.push(0, 1);
  stack1.push(1, 2);

  // Copy constructor
  MultiStack<int> stack2(stack1);
  EXPECT_EQ(stack2.top(0), 1);

  // Move constructor
  MultiStack<int> stack3(std::move(stack2));
  EXPECT_EQ(stack3.top(0), 1);
  EXPECT_TRUE(stack2.isEmpty());

  // Copy assignment
  MultiStack<int> stack4(10, 3);
  stack4 = stack1;
  EXPECT_EQ(stack4.top(0), 1);

  // Move assignment
  MultiStack<int> stack5(10, 3);
  stack5 = std::move(stack4);
  EXPECT_EQ(stack5.top(0), 1);
  EXPECT_TRUE(stack4.isEmpty());
}
