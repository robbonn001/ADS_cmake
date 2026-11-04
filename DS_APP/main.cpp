// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iomanip>
#include <iostream>

#include "../Algorithms/easy_example.h"
#include "../LibMultiStack/MultiStack.h"

void test() {
  int a, b;
  float result;

  a = 1;
  b = 4;

  try {
    result = division(a, b);
    std::cout << a << " / " << b << " = " << std::setprecision(2) << result
              << std::endl;
  } catch (std::exception err) {
    std::cerr << err.what() << std::endl;
  }

  a = 1;
  b = 0;

  try {
    result = division(a, b);
    std::cout << a << " / " << b << " = " << std::setprecision(2) << result
              << std::endl;
  } catch (std::exception err) {
    std::cerr << err.what() << std::endl;
  }
}

int main() {
  // MultiStack<int> stack(10, 3);

  //// Заполняем секторы: 1-й=1 эл, 2-й=3 эл, 3-й=2 эл
  // stack.push(0, 1);
  // stack.push(1, 2);
  // stack.push(1, 3);
  // stack.push(1, 4);
  // stack.push(2, 5);
  // stack.push(2, 6);

  // std::cout << stack;
  // stack.push(1, 8);
  // std::cout << stack;

  MultiStack<int> stack(10, 3);

  stack.push(0, 1);
  stack.push(0, 2);
  stack.push(0, 3);

  stack.push(1, 4);
  stack.push(1, 5);
  stack.push(1, 6);

  stack.push(2, 7);
  stack.push(2, 8);

  std::cout << stack;

  stack.push(1, 9);

  std::cout << stack;
}

#endif  // EASY_EXAMPLE
