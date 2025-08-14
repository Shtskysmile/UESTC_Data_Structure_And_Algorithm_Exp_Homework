#ifndef HPINT_H
#define HPINT_H
#define Maxsize 100000
#include <iostream>
#include <string>

using namespace std;

class HPint {
private:
    int* array; // 存储每一位的数据
    string number;  // 存储了字符串形式的数据
    string flag;    // 符号
    int length; // 十进制数有多少位

public:
    // 构造函数
    HPint();
    HPint(string number);
    HPint(int integer);
    HPint(const HPint& another);

    // 赋值运算符重载
    HPint& operator=(const HPint& another);

    // 析构函数
    ~HPint();

    // 成员函数
    int getlength() const;
    void check_zero();
    HPint getabs() const;

    // 友元函数
    friend ostream& operator<<(ostream& out, HPint a);

    // 比较运算符重载
    bool operator<(const HPint& another) const;
    bool operator>(const HPint& another) const;
    bool operator==(const HPint& another) const;
    bool operator<=(const HPint& another) const;
    bool operator>=(const HPint& another) const;
    bool operator!=(const HPint& another) const;

    // 取反运算符重载
    HPint operator-() const;
    // 加减乘运算符重载
    HPint operator+(const HPint& another) const;
    HPint operator-(const HPint& another) const;
    HPint operator*(const HPint& another) const;

    // 左移右移运算符重载
    HPint operator<<(int j);
    HPint operator>>(int j);

    // 除法运算符重载
    HPint operator/(const HPint& another) const;
};

#endif // HPINT_H
