#include "ExpressionEvaluator.hpp"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv)
{
    string expression = argv[1];
    ExpressionEvaluator evaluator;
    auto result = evaluator.evaluate(expression);
    cout << result;
    return 0;
}