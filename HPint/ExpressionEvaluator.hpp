#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <stack>
#include "HPint.hpp"  // 引入HPint类

// ExpressionEvaluator类用于计算数学表达式
class ExpressionEvaluator {
public:
    // 构造函数
    ExpressionEvaluator() = default;

    // 评估输入的数学表达式，返回结果
    HPint evaluate(const std::string& expression);

private:
    // 获取运算符的优先级，返回值越大优先级越高
    int precedence(char op);

    // 执行运算操作（两数一运算符）
    void performOperation(std::stack<HPint>& values, std::stack<char>& operators);
};

#endif // EXPRESSION_EVALUATOR_H
