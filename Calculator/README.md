# 四则计算机项目介绍

## 项目结构

1. HPint.hpp与HPint.cpp对应了大整数类
2. ExpressionEvaluator.hpp和ExpressionEvaluator.cpp对应了解析表达式的类
3. main.cpp是主函数，编译可以生成计算器的内核main.exe
4. Calculator.py是具有图形化界面的Python程序。通过命令行方式调用main.exe内核实现运算。

## 使用说明

1. 编译操作：请最好使用g++编译器，否则可能有头文件缺失的bug

   ```bash
   g++ -o main.exe main.cpp Evaluator.cpp HPint.cpp
   ```
2. 启动计算器：请cd到Calculator目录下启动Python程序，否则Python程序调用命令行时候会找不到main.exe内核位置导致报错。如果没有安装tkinker包，请使用pip命令安装

   ```bash
   cd Calculator
   pip install tkinker
   python Calculator.py
   ```
