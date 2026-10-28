// Copyright 2026 Igor
#include <string>
#include "../Algorithms/brackets.h"

bool checkBreackets(std::string expression) {
    StackOnMass<char> stack(expression.size());
    for (char symbol : expression) {
        if (symbol =='(' || symbol == '[' || symbol == '{') {
            stack.push(symbol);
        } else {
            if (symbol == ')' || symbol == ']' || symbol == '}') {
                if (stack.isEmpty()) return false;
                char openBracket = stack.pop();
                if (!((openBracket == '(' && symbol == ')') ||
                    (openBracket == '[' && symbol == ']') ||
                    (openBracket == '{' && symbol == '}'))) return false;
            }
        }
    }
    return stack.isEmpty();
}
