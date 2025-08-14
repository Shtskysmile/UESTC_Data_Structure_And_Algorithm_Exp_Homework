#include <bits/stdc++.h>
#include <cstdlib>
#include "ExpressionEvaluator.hpp"

using namespace std;

// 评估输入的数学表达式
HPint ExpressionEvaluator::evaluate(const string& expression) {
    stack<HPint> values;  // 存储操作数
    stack<char> operators; // 存储运算符

    int n = expression.length();
    bool expectOperand = true;  // 用于判断是否期望下一个token是操作数

    for (int i = 0; i < n; ++i) {
        char ch = expression[i];

        if (isspace(ch)) {
            continue;  // 跳过空格
        }

        if (isdigit(ch) || (ch == '-' && expectOperand)) {
            // 如果是数字或期望操作数时遇到的负号，构建数字并推入栈中
            string num;
            if (ch == '-') {
                num += ch;
                ++i;
            }
            while (i < n && isdigit(expression[i])) {
                num += expression[i++];
            }
            --i;  // 因为多加了一个i，回退
            values.push(HPint(num));
            expectOperand = false;
        }
        else if (ch == '(') {
            operators.push(ch);
            expectOperand = true;
        }
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                performOperation(values, operators);
            }
            if (!operators.empty()) {
                operators.pop();  // 弹出 '('
            }
            expectOperand = false;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(ch)) {
                performOperation(values, operators);
            }
            operators.push(ch);
            expectOperand = true;
        }
        else {
            cout << "Invalid char found!";
            exit(1);
        }
    }

    while (!operators.empty()) {
        performOperation(values, operators);
    }

    if (values.size() != 1) {
        cout << "Invalid Expression";
        exit(1);
    }
    return values.top();
}


// 获取运算符的优先级，返回值越大优先级越高
int ExpressionEvaluator::precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // 对于非法的运算符返回0
}

// 执行运算操作（两数一运算符）
void ExpressionEvaluator::performOperation(stack<HPint>& values, stack<char>& operators) {
    // 确保操作符栈和操作数栈有足够的元素
    if (values.size() < 2) {
        cout << "Invalid Expression";
        exit(1);
    }

    HPint b = values.top();
    values.pop();
    HPint a = values.top();
    values.pop();
    char op = operators.top();
    operators.pop();

    HPint result;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                cout << "Zero Division";
                exit(1);
            }
            result = a / b;
            break;
        default:
            cout << "Invalid Operator";
            exit(1);
    }

    values.push(result);
}
