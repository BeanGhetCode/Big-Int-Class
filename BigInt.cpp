#include "BigInt.h"
// Constructor mặc định
BigInt::BigInt() : length(1), isNegative(false) {
    fill(digits, digits + MAX_DIGITS, 0);
}

// Constructor chuyển chuỗi thành BigInt
BigInt::BigInt(const string& number) {
    fill(digits, digits + MAX_DIGITS, 0);
    isNegative = (number[0] == '-');
    length = number.length() - (isNegative ? 1 : 0);
    for (int i = 0; i < length; ++i) {
        digits[length - i - 1] = number[i + (isNegative ? 1 : 0)] - '0';
    }
}

// Nhập số BigInt
void BigInt::inputBigInt() {
    string input;
    cin >> input;

    // Reset BigInt về giá trị mặc định
    fill(digits, digits + MAX_DIGITS, 0);
    isNegative = (input[0] == '-');  // Kiểm tra xem số có âm không

    // Xác định chiều dài của chuỗi
    length = input.length() - (isNegative ? 1 : 0);

    // Lưu các chữ số ngược lại trong mảng digits
    for (int i = 0; i < length; ++i) {
        digits[length - i - 1] = input[i + (isNegative ? 1 : 0)] - '0';
    }
}

// Hàm hiển thị số BigInt
void BigInt::display() const {
    if (isNegative) cout << '-';
    for (int i = length - 1; i >= 0; --i) {
        cout << digits[i];
    }
}

// Hàm cộng hai số BigInt
BigInt BigInt::operator+(const BigInt& other) const {
    if (isNegative && !other.isNegative) {
        return other - (-*this);
    }
    if (!isNegative && other.isNegative) {
        return *this - (-other);
    }

    BigInt result;
    result.isNegative = isNegative;
    result.length = max(length, other.length);
    int carry = 0;

    for (int i = 0; i < result.length; ++i) {
        int sum = digits[i] + other.digits[i] + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry) {
        result.digits[result.length++] = carry;
    }

    return result;
}

// Hàm trừ hai số BigInt
BigInt BigInt::operator-(const BigInt& other) const {
    if (isNegative && other.isNegative) {
        return (-other) - (-*this);
    }
    if (!isNegative && other.isNegative) {
        return *this + (-other);
    }
    if (isNegative && !other.isNegative) {
        return -((-*this) + other);
    }

    BigInt result;
    result.isNegative = isNegative;

    bool swapped = false;
    const BigInt* larger = this;
    const BigInt* smaller = &other;

    if (compare(*this, other) < 0) {
        swapped = true;
        larger = &other;
        smaller = this;
    }

    result.length = larger->length;
    int borrow = 0;

    for (int i = 0; i < result.length; ++i) {
        int diff = larger->digits[i] - smaller->digits[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.digits[i] = diff;
    }

    while (result.length > 1 && result.digits[result.length - 1] == 0) {
        --result.length;
    }

    if (swapped) {
        result.isNegative = !result.isNegative;
    }

    return result;
}

// Chuyển đổi BigInt thành int
int BigInt::toInt() const {
    long long value = 0;
    for (int i = length - 1; i >= 0; --i) {
        value = value * 10 + digits[i];
    }
    if (isNegative) value = -value;
    return static_cast<int>(value);
}

// Chuyển đổi BigInt thành cơ số 16
string BigInt::toHex() const {
    long long value = toInt();
    stringstream ss;
    ss << hex << uppercase << value;
    return ss.str();
}

// Hàm so sánh
int BigInt::compare(const BigInt& a, const BigInt& b) {
    if (a.length != b.length) {
        return a.length - b.length;
    }
    for (int i = a.length - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i]) {
            return a.digits[i] - b.digits[i];
        }
    }
    return 0;
}

string BigInt::CompareBigInt(const BigInt& a, const BigInt& b) {
    int cmpResult = BigInt::compare(a, b);

    if (cmpResult > 0) {
        return ">";
    }
    else if (cmpResult < 0) {
        return "<";
    }
    else {
        return "=";
    }
}

// Toán tử ==
bool BigInt::operator==(const BigInt& other) const {
    return compare(*this, other) == 0;
}

// Toán tử !=
bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

// Toán tử <
bool BigInt::operator<(const BigInt& other) const {
    return compare(*this, other) < 0;
}

// Toán tử >
bool BigInt::operator>(const BigInt& other) const {
    return compare(*this, other) > 0;
}

// Toán tử <=
bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

// Toán tử >=
bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

// Lấy số đối
BigInt BigInt::operator-() const {
    BigInt result = *this;
    result.isNegative = !isNegative;
    return result;
}

// Nhân 2 số BigInt
BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.isNegative = (isNegative != other.isNegative);  // Kết quả có dấu âm nếu một trong hai số âm
    fill(result.digits, result.digits + MAX_DIGITS, 0);  // Khởi tạo mảng digits của kết quả

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < other.length; ++j) {
            result.digits[i + j] += digits[i] * other.digits[j];
            // Điều chỉnh giá trị dư
            if (result.digits[i + j] >= 10) {
                result.digits[i + j + 1] += result.digits[i + j] / 10;
                result.digits[i + j] %= 10;
            }
        }
    }

    // Xác định chiều dài kết quả
    result.length = length + other.length;
    while (result.length > 1 && result.digits[result.length - 1] == 0) {
        --result.length;
    }

    return result;
}

// Chia 2 số BigInt lấy phần nguyên
BigInt BigInt::operator/(const BigInt& divisor) const {
    if (divisor == BigInt("0")) {
        throw invalid_argument("Cannot divide by zero");
    }

    // Kết quả cuối cùng sẽ là thương và có dấu âm nếu một trong hai số là âm
    BigInt quotient;
    quotient.isNegative = (isNegative != divisor.isNegative);
    quotient.length = length;
    fill(quotient.digits, quotient.digits + MAX_DIGITS, 0);

    BigInt remainder;
    remainder.length = 0;

    // Bắt đầu duyệt từng chữ số từ trái sang phải
    for (int i = length - 1; i >= 0; --i) {
        // Dịch chuyển remainder sang trái (nhân 10) và thêm chữ số mới từ dividend
        remainder = remainder * BigInt("10") + BigInt(to_string(digits[i]));

        // Tìm số lần mà số chia có thể trừ từ remainder
        int digitQuotient = 0;
        while (remainder >= divisor) {
            remainder = remainder - divisor;
            ++digitQuotient;
        }

        // Gán chữ số thương tìm được vào kết quả
        quotient.digits[i] = digitQuotient;
    }

    // Loại bỏ các chữ số 0 thừa trong thương
    while (quotient.length > 1 && quotient.digits[quotient.length - 1] == 0) {
        --quotient.length;
    }

    return quotient;
}

// Chia 2 số BigInt lấy phần dư
BigInt BigInt::operator%(const BigInt& divisor) const {
    if (divisor == BigInt("0")) {
        throw invalid_argument("Cannot divide by zero");
    }

    BigInt remainder;
    remainder.isNegative = isNegative;  // Duy trì dấu âm của số dư
    fill(remainder.digits, remainder.digits + MAX_DIGITS, 0);  // Khởi tạo mảng digits của phần dư

    // Duyệt từ chữ số lớn nhất đến nhỏ nhất
    for (int i = length - 1; i >= 0; --i) {
        // Chuyển remainder sang trái (nhân 10) và thêm chữ số mới từ dividend
        BigInt temp;
        temp.digits[0] = digits[i];
        temp.length = 1;
        remainder = remainder * BigInt("10") + temp;

        // Tìm phần dư khi chia
        while (remainder >= divisor) {
            remainder = remainder - divisor;
        }
    }

    // Loại bỏ các số 0 dư thừa ở phần đầu
    while (remainder.length > 1 && remainder.digits[remainder.length - 1] == 0) {
        --remainder.length;
    }

    return remainder;
}

//Giá trị tuyệt đối
BigInt BigInt:: abs() const{
    BigInt result = *this;
    result.isNegative = false;
    return result;
}

// Lũy thừa
BigInt BigInt::power(int exponent) const {
    if (exponent < 0) {
        throw invalid_argument("Exponent must be non-negative");
    }

    BigInt result("1");

    // Nếu số mũ là 0, trả về 1
    if (exponent == 0) {
        return result;
    }

    BigInt base = *this;

    while (exponent > 0) {
        if (exponent % 2 == 1) {  // Nếu số mũ hiện tại là số lẻ
            result = result * base;
        }

        base = base * base;  // Cập nhật cơ sở
        exponent /= 2;  // Chia đôi số mũ
    }

    return result;
}

// Căn bậc 2
BigInt BigInt::sqrt() const {
    BigInt low("0");
    BigInt high = *this;
    BigInt mid;
    BigInt midSquared;

    while (low < high) {
        mid = (low + high) / BigInt("2");
        midSquared = mid * mid;

        if (midSquared == *this) {
            return mid;  
        }
        if (midSquared < *this) {
            low = mid + BigInt("1");
        }
        else {
            high = mid - BigInt("1");
        }
    }

    return high;  
}
// Căn bậc 3
BigInt BigInt::cbrt() const {
    if (*this == BigInt("0") || *this == BigInt("1")) {
        return *this;
    }

    BigInt low("0");
    BigInt high = *this;
    BigInt mid;
    BigInt midCubed;

    while (low < high) {
        mid = (low + high) / BigInt("2"); // Chia cho 2 để tìm giá trị giữa
        midCubed = mid * mid * mid;

        if (midCubed == *this) {
            return mid;  
        }
        if (midCubed < *this) {
            low = mid + BigInt("1");  
        }
        else {
            high = mid - BigInt("1"); 
        }
    }
    return high;
}