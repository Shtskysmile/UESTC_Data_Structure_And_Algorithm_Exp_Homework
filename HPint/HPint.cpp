#include "HPint.hpp"

HPint::HPint()
{
    /**
     * @brief 默认初始化为+0
     *
     */
    this->array = new int[Maxsize];
    for (int i = 0; i < Maxsize; i++) {
        this->array[i] = 0;
    }
    this->length = 0;
    this->flag = "+";
}
HPint::HPint(string number)
{
    /**
     * @brief 字符串初始化数字
     *
     */
    if (number[0] == '+') {
        this->flag = "+";
        number = number.substr(1);
    } else if (number[0] == '-') {
        this->flag = "-";
        number = number.substr(1);
    } else {
        this->flag = "+";
    }
    this->number = number;
    this->length = number.size();
    this->array = new int[Maxsize];
    for (int i = 0; i < length; i++) {
        array[i] = number[number.size() - i - 1] - '0';
    }
    for (int i = length; i < Maxsize; i++) {
        array[i] = 0;
    }
    if (number == "0") {
        this->flag = "+";
    }
}
HPint::HPint(int integer)
{
    /**
     * @brief 整数初始化
     *
     */
    if (integer >= 0) {
        flag = "+";
    } else {
        flag = "-";
        integer = -integer;
    }
    this->array = new int[Maxsize];
    for (int i = 0; i < Maxsize; i++) {
        this->array[i] = 0;
    }
    this->length = 0;
    if (integer == 0) {
        this->length = 1;
        this->flag = "+";
        this->number.append("0");
    }
    for (int i = 0;; i++) {
        if (integer != 0) {
            this->array[i] = (integer % 10);
            integer /= 10;
            this->length++;
        } else {
            break;
        }
    }
    this->number.resize(this->length);
    for (int i = 0; i < this->length; i++) {
        this->number[i] = this->array[this->number.size() - 1 - i] + '0';
    }
}
HPint::HPint(const HPint& another)
{
    /**
     * @brief 拷贝构造函数
     *
     */
    this->flag = another.flag;
    this->array = new int[Maxsize];
    this->length = another.length;
    for (int i = 0; i < Maxsize; i++) {
        array[i] = another.array[i];
    }
    this->number = another.number;
}
HPint& HPint::operator=(const HPint& another)
{
    /**
     * @brief 赋值运算符重载
     *
     */
    this->flag = another.flag;
    delete[] this->array;
    this->array = new int[Maxsize];
    this->length = another.length;
    for (int i = 0; i < Maxsize; i++) {
        array[i] = another.array[i];
    }
    this->number = another.number;
    return *this;
}
HPint::~HPint()
{
    delete[] this->array;
}
int HPint::getlength() const
{
    return this->length;
}
void HPint::check_zero()
{
    if (this->number == "0") {
        this->flag = "+";
    }
}
HPint HPint::getabs() const
{
    HPint temp = *this;
    temp.flag = "+";
    return temp;
}
ostream& operator<<(ostream& out, HPint a)
{
    if (a.flag == "-") {
        out << a.flag << a.number;
    } else {
        out << a.number;
    }
    return out;
}
bool HPint::operator<(const HPint& another) const
{
    if (this->flag == "+" and another.flag == "-") {
        return false;
    }
    if (this->flag == "-" and another.flag == "+") {
        return true;
    }
    if (this->flag == "+" and another.flag == "+") {
        if (this->length < another.length) {
            return true;
        } else if (this->length > another.length) {
            return false;
        } else {
            for (int i = 0; i < this->length; i++) {
                if (this->number[i] < another.number[i]) {
                    return true;
                } else if (this->number[i] > another.number[i]) {
                    return false;
                } else {
                    ;
                }
            }
            return false;
        }
    }
    if (this->flag == "-" and another.flag == "-") {
        if (this->length < another.length) {
            return false;
        } else if (this->length > another.length) {
            return true;
        } else {
            for (int i = 0; i < this->length; i++) {
                if (this->number[i] < another.number[i]) {
                    return false;
                } else if (this->number[i] > another.number[i]) {
                    return true;
                } else {
                    ;
                }
            }
            return false;
        }
    }
}
bool HPint::operator>(const HPint& another) const
{
    if (this->flag == "+" and another.flag == "-") {
        return true;
    }
    if (this->flag == "-" and another.flag == "+") {
        return false;
    }
    if (this->flag == "+" and another.flag == "+") {
        if (this->length < another.length) {
            return false;
        } else if (this->length > another.length) {
            return true;
        } else {
            for (int i = 0; i < this->length; i++) {
                if (this->number[i] < another.number[i]) {
                    return false;
                } else if (this->number[i] > another.number[i]) {
                    return true;
                } else {
                    ;
                }
            }
            return false;
        }
    }
    if (this->flag == "-" and another.flag == "-") {
        if (this->length < another.length) {
            return true;
        } else if (this->length > another.length) {
            return false;
        } else {
            for (int i = 0; i < this->length; i++) {
                if (this->number[i] < another.number[i]) {
                    return true;
                } else if (this->number[i] > another.number[i]) {
                    return false;
                } else {
                    ;
                }
            }
            return false;
        }
    }
}
bool HPint::operator==(const HPint& another) const
{
    return this->number == another.number and (this->flag == another.flag);
}
bool HPint::operator<=(const HPint& another) const
{
    return not(*this > another);
}
bool HPint::operator>=(const HPint& another) const
{
    return not(*this < another);
}
bool HPint::operator!=(const HPint& another) const
{
    return this->number != another.number or (this->flag != another.flag);
}
HPint HPint::operator-() const
{
    HPint temp = *this;
    if (temp.number == "0") {
        return temp;
    }
    if (this->flag == "+") {
        temp.flag = "-";
    } else {
        temp.flag = "+";
    }
    return temp;
}
HPint HPint::operator+(const HPint& another) const
{
    // 如果两个HPint对象的符号都为正
    if (this->flag == "+" and another.flag == "+") {
        // 计算两个HPint对象的长度，并加1
        int lens = max(this->length, another.length) + 1;
        // 创建一个新的HPint对象Temp
        HPint Temp;
        Temp.length = lens;
        // 遍历两个HPint对象的每一位，进行相加
        for (int i = 0; i < lens - 1; i++) {
            Temp.array[i] += this->array[i] + another.array[i];
            Temp.array[i + 1] += Temp.array[i] / 10;
            Temp.array[i] %= 10;
        }
        // 如果最高位为0，则将长度减1
        if (Temp.array[lens - 1] == 0) {
            Temp.length--;
            lens--;
        }
        // 将Temp对象的数组转换为字符串
        Temp.number.resize(Temp.length);
        for (int i = 0; i < Temp.length; i++) {
            Temp.number[i] = Temp.array[Temp.number.size() - 1 - i] + '0';
        }
        // 返回Temp对象
        return Temp;
    // 如果第一个HPint对象的符号为负，第二个HPint对象的符号为正
    } else if (this->flag == "-" and another.flag == "+") {
        // 返回第一个HPint对象减去第二个HPint对象的相反数
        return (another - (-(*this)));
    // 如果第一个HPint对象的符号为正，第二个HPint对象的符号为负
    } else if (this->flag == "+" and another.flag == "-") {
        // 返回第一个HPint对象减去第二个HPint对象的相反数
        return (*this - (-another));
    // 如果两个HPint对象的符号都为负
    } else if (this->flag == "-" and another.flag == "-") {
        // 返回第一个HPint对象的相反数加上第二个HPint对象的相反数
        return -(-(*this) + (-(another)));
    }
}
// 重载减法运算符
HPint HPint::operator-(const HPint& another) const
{
    // 如果两个HPint对象相等，则返回0
    if (*this == another) {
        return HPint("0");
    }
    // 如果两个HPint对象都是正数
    if (this->flag == "+" and another.flag == "+") {
        HPint temp;
        HPint a = *this;
        HPint b = another;
        // 如果被减数小于减数，则交换两个HPint对象
        if (*this < another) {
            swap(a, b);
            temp.flag = "-";
        }
        temp.length = a.length;
        // 进行减法运算
        for (int i = 0; i < temp.length; i++) {
            if (a.array[i] < b.array[i]) {
                a.array[i] += 10;
                a.array[i + 1] -= 1;
            }
            temp.array[i] = a.array[i] - b.array[i];
        }
        // 去除结果中的前导0
        for (int i = temp.length - 1; i >= 0; i--) {
            if (temp.array[i] != 0) {
                temp.length = i + 1;
                break;
            }
        }
        // 将结果转换为字符串
        temp.number.resize(temp.length);
        for (int i = 0; i < temp.length; i++) {
            temp.number[i] = temp.array[temp.number.size() - 1 - i] + '0';
        }
        return temp;
    // 如果被减数是正数，减数是负数
    } else if (this->flag == "+" and another.flag == "-") {
        return ((*this) + (-another));
    // 如果被减数是负数，减数是正数
    } else if (this->flag == "-" and another.flag == "+") {
        return (-(-(*this) + another));
    // 如果被减数和减数都是负数
    } else if (this->flag == "-" and another.flag == "-") {
        return (-another) - (-(*this));
    }
}
// 重载乘法运算符，实现两个高精度整数相乘
HPint HPint::operator*(const HPint& another) const
{
    // 创建一个临时的高精度整数，初始值为0
    HPint temp("0");
    // 如果其中一个高精度整数为0，则返回0
    if (this->number == "0" or another.number == "0") {
        return temp;
    }
    // 如果两个高精度整数的符号不同，则结果为负数
    if (this->flag != another.flag) {
        temp.flag = "-";
    } else {
        temp.flag = "+";
    }
    // 计算结果的长度，长度为两个高精度整数的长度之和再加5
    temp.length = this->length + another.length + 5;
    // 遍历两个高精度整数的每一位，进行乘法运算
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < another.length; j++) {
            temp.array[i + j] += this->array[i] * another.array[j];
            temp.array[i + j + 1] += temp.array[i + j] / 10;
            temp.array[i + j] %= 10;
        }
    }
    // 去掉结果中的前导0
    for (int i = temp.length - 1; i >= 0; i--) {
        if (temp.array[i] != 0) {
            temp.length = i + 1;
            break;
        }
    }
    // 将结果转换为字符串
    temp.number.resize(temp.length);
    for (int i = 0; i < temp.length; i++) {
        temp.number[i] = temp.array[temp.number.size() - 1 - i] + '0';
    }
    // 返回结果
    return temp;
}
// 重载<<运算符，将HPint类型的对象向左移动j位
HPint HPint::operator<<(int j)
{
    // 如果j为0，则直接返回当前对象
    if (j == 0) {
        return *this;
    }
    // 如果当前对象为0，则直接返回当前对象
    if (*this == HPint("0")) {
        return *this;
    }
    // 将当前对象的长度增加j
    this->number.resize(this->length + j, 48);
    this->length += j;
    // 将当前对象的数字部分复制到新的数组中
    for (int i = 0; i < this->length; i++) {
        this->array[this->number.size() - 1 - i] = this->number[i] - '0';
    }
    // 返回当前对象
    return *this;
}
// 重载>>运算符，将HPint类型的对象向右移动j位
HPint HPint::operator>>(int j)
{
    // 如果j为0，则直接返回当前对象
    if (j == 0) {
        return *this;
    }
    // 如果当前对象为0，则直接返回当前对象
    if (*this == HPint("0")) {
        return *this;
    }
    // 将number数组的大小调整为length-j
    this->number.resize(this->length - j);
    // 将length调整为length-j
    this->length -= j;
    // 将number数组中的元素依次放入array数组中
    for (int i = 0; i < this->length; i++) {
        this->array[this->number.size() - 1 - i] = this->number[i] - '0';
    }
    // 将array数组中剩余的位置置为0
    for (int i = this->length; i < 500; i++) {
        this->array[i] = 0;
    }
    // 返回当前对象
    return *this;
}
HPint HPint::operator/(const HPint& another) const
{
    // 如果被除数等于0，则抛出异常
    if (another.number == "0") {
        throw 0;
    }
    // 初始化结果为0
    HPint result = HPint(0);
    // 如果被除数小于除数或者被除数为0，则返回结果为0
    if (*this < another or this->number == "0") {
        return result;
    }
    // 获取被除数的绝对值
    HPint place = this->getabs();
    // 遍历被除数和除数的长度差
    for (int j = 0; this->length - another.length - j >= 0; j++) {
        // 遍历除数的每一位
        for (int i = 1; i < 10; i++) {
            // 获取除数的绝对值并左移
            HPint temp = another.getabs();
            temp << (this->length - another.length - j);
            // 如果除数的绝对值大于被除数的绝对值，则将结果加1并跳出循环
            if (temp > place) {
                result << (1);
                result = result + HPint(i - 1);
                break;
            } else {
                // 否则将被除数的绝对值减去除数的绝对值
                place = place - temp;
            }
        }
    }
    // 如果被除数和除数的符号不同，则将结果符号设为负号
    if (this->flag != another.flag) {
        result.flag = "-";
    }
    // 返回结果
    return result;
}