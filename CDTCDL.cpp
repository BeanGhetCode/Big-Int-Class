#include <iostream>
#include <string>
#include "BigInt.h"

using namespace std;

void printMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. BigIn to Hex" << endl;
    cout << "2. BigInt to Int" << endl;
    cout << "3. Sum" << endl;
    cout << "4. Difference" << endl;
    cout << "5. Product" << endl;
    cout << "6. Division" << endl;
    cout << "7. Remainder" << endl;
    cout << "8. Opposite" << endl;
    cout << "9. Absolute" << endl;
    cout << "10. Power" << endl;
    cout << "11. Compare" << endl;
    cout << "12. Square root" << endl;
    cout << "13. Cube root" << endl;
    cout << "14. UCLN " << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

//hàm tìm ước chung lớn nhất 2 số BigInt
BigInt GCD(const BigInt& a, const BigInt& b) {
    BigInt A = a;
    BigInt B = b;

    // Nếu B lớn hơn A, hoán đổi A và B
    if (B > A) {
        BigInt temp = A;
        A = B;
        B = temp;
    }

    // Thuật toán Euclid để tìm UCLN
    while (B != BigInt("0")) {
        BigInt temp = B;
        B = A % B;
        A = temp;
    }

    return A;
}


int main() {

    int choice, num;
    BigInt num1, num2, result;
    string str;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter BigInt: ";
            num1.inputBigInt(); 
            str = num1.toHex();  
            cout << "Hex: " << str << endl;  
            break;
        case 2:
            cout << "Enter BigInt: ";
            num1.inputBigInt();
            num = num1.toInt();
            cout << "Dạng Int: " << num << endl;
            break;
        case 3:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();
            result = num1 + num2;
            cout << "Sum : ";
            result.display();
            break;
        case 4:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();
            result = num1 - num2;
            cout << "Difference: ";
            result.display();
            break;
        case 5:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();
            result = num1 * num2;
            cout << "Product: ";
            result.display();
            break;
        case 6:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();
            result = num1 / num2;
            cout << "Division: ";
            result.display();
            break;
        case 7:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();
            result = num1 % num2;
            cout << "Remainder: ";
            result.display();
            break;
        case 8:
            cout << "num 1 =  ";
            num1.inputBigInt();
            result = num1.abs();
            cout << "Opposite: ";
            result.display();
            break;
        case 9:
            cout << "num 1 =  ";
            num1.inputBigInt();
            result = -(num1);
            cout << "Absolute: ";
            result.display();
            break;
        case 10:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "enter exponent =  ";
            int ex;
            cin >> ex;
            result = num1.power(ex);
            cout << "Power with exponent: "<< ex <<": ";
            result.display();
            break;
        case 11:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();
            cout << "Compare: ";

            num1.display();
            str = num1.CompareBigInt(num1,num2);
            cout << " " << str << " ";
            num2.display();
            break;
        case 12:
            cout << "num 1 =  ";
            num1.inputBigInt();
            result = num1.sqrt();
            cout << "Square root: ";
            result.display();
            break;
        case 13:
            cout << "num 1 =  ";
            num1.inputBigInt();
            result = num1.cbrt();
            cout << "Cube root: ";
            result.display();
            break;
        case 14:
            cout << "num 1 =  ";
            num1.inputBigInt();
            cout << "num 2 = ";
            num2.inputBigInt();

            result = GCD(num1, num2);
            cout << "UCLN: ";
            result.display();
            break;
        case 0:
            cout << "Exit." << endl;
            break;

        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}


