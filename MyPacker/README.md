# 项目说明

## 项目结构

1. Packer.cpp和Packer.hpp对应了压缩类
2. UnPacker.cpp和UnPacker.hpp对应了解压缩类
3. pak.cpp和pak.exe对应了压缩程序。
4. unpak.cpp和unpak.exe对应了解压缩程序。
5. main.py是具有图形化界面的解压缩程序。img文件夹存放了显示用的图片。

## 使用教程

1. 编译：推荐g++编译器。
   ```bash
   g++ -o pak.exe pak.cpp Packer.cpp
   g++ -o unpak.exe unpak.cpp UnPacker
   ```
2. 运行：图形化运行：
   ```bash
   cd MyPacker
   pip install tkinker
   python main.py
   ```
3. 也可以使用默认打开方式对.myzip文件进行解压缩，详见实验报告。
