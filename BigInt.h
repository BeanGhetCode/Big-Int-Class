#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

const int MAX_DIGITS = 100; // Định nghĩa kích thước tối đa cho BigInt

class BigInt {
private:
    int digits[MAX_DIGITS];
    int length;
    bool isNegative;

public:
    // Constructor mặc định
    BigInt();

    // Constructor chuyển chuỗi thành BigInt
    BigInt(const string& number);

    // Nhập số BigInt
    void inputBigInt();

    // Hàm hiển thị số BigInt
    void display() const;

    // Hàm cộng hai số BigInt
    BigInt operator+(const BigInt& other) const;

    // Hàm trừ hai số BigInt
    BigInt operator-(const BigInt& other) const;

    // Chuyển đổi BigInt thành int
    int toInt() const;

    // Chuyển đổi BigInt thành cơ số 16
    string toHex() const;

    // Hàm so sánh
    static int compare(const BigInt& a, const BigInt& b);
    string CompareBigInt(const BigInt& a, const BigInt& b);

    // Toán tử ==
    bool operator==(const BigInt& other) const;

    // Toán tử !=
    bool operator!=(const BigInt& other) const;

    // Toán tử <
    bool operator<(const BigInt& other) const;

    // Toán tử >
    bool operator>(const BigInt& other) const;

    // Toán tử <=
    bool operator<=(const BigInt& other) const;

    // Toán tử >=
    bool operator>=(const BigInt& other) const;

    // Lấy số đối
    BigInt operator-() const;

    // Nhân 2 số BigInt
    BigInt operator*(const BigInt& other) const;

    // Chia 2 số BigInt
    BigInt operator/(const BigInt& divisor) const;

    // Chia lấy dư
    BigInt operator%(const BigInt& divisor) const;

    // Giá trị tuyệt đối
    BigInt abs() const;

    // Lũy thừa
    BigInt power(int exponent) const;

    // Căn bậc 2
    BigInt sqrt() const;

    // Căn bậc 3
    BigInt cbrt() const;
};

#endif // BIGINT_H
