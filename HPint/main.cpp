#include "ExpressionEvaluator.hpp"
#include <string>
using namespace std;
int main() {
    ExpressionEvaluator evaluator;
    cout << "please input an expression" << endl;
    string expression;
    getline(cin, expression);
    HPint result = evaluator.evaluate(expression);
    cout << "Result: " << result << endl;  // 输出 3
    return 0;
}
