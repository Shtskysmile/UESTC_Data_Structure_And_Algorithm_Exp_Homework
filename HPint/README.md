# 项目介绍

## 项目结构

1. ExpressionEvaluator.cpp和ExpressionEvaluator.hpp对应了表达式解析类。
2. HPint.cpp和HPint.hpp对应了大整数类。
3. main.cpp是主程序，输入一个表达式得到正确的结果。
4. main.exe是编译好的可执行程序。

## 使用说明

1. 编译：编译器最好使用g++，不会发生头文件缺失问题。
   ```bash
   g++ -o main.exe main.cpp HPint.cpp Evaluator.cpp
   ```
2. 运行：命令行运行main.exe则可。
   ```bash
   main.exe
   ```
