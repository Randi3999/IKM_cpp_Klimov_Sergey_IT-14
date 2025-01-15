#include "header.h"

// Функция для проверки, является ли степень многочлена натуральным числом
int inputDegree() {
    int n;
    cout << "Введите степень многочлена (неотрицательное число n): ";
    while (true) {
        cin >> n;

        if (cin.fail() || n < 0) {
            cout << "Ошибка! Введите неотрицательное число (n >= 0): ";
            cin.clear(); // Сброс флага ошибки
            cin.ignore(10000, '\n'); // Очистка ввода
        } else {
            return n; // Корректное значение
        }
    }
}

// Функция для ввода коэффициентов многочлена с проверкой
void inputCoefficients(string* coefficients, int n) {
    cout << "Введите коэффициенты многочлена (от старшего к младшему):" << endl;

    for (int i = 0; i <= n; ++i) {
        cout << "Введите коэффициент a" << n - i << ": ";
        cin >> coefficients[i];
        // Проверка, что введено корректное число
        for (char c : coefficients[i]) {
            if (!isdigit(c) && c != '-') {
                cout << "Ошибка! Коэффициент должен быть целым числом. Повторите ввод." << endl;
                --i; // Повторяем ввод для текущего коэффициента
                break;
            }
        }
    }
}

// Функция для умножения большого числа на маленькое число (для x^k)
string multiplyBigInt(const string& num, int x) {
    if (x == 0) return "0";

    int carry = 0;
    string result = "";

    for (int i = num.size() - 1; i >= 0; --i) {
        int digit = num[i] - '0';
        int product = digit * x + carry;
        result = char((product % 10) + '0') + result;
        carry = product / 10;
    }

    if (carry > 0) {
        result = to_string(carry) + result;
    }

    return result;
}

// Функция для сложения двух больших чисел
string addBigInt(const string& num1, const string& num2) {
    string result = "";
    int carry = 0;

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? (num1[i] - '0') : 0;
        int digit2 = (j >= 0) ? (num2[j] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        result = char((sum % 10) + '0') + result;
        carry = sum / 10;

        --i;
        --j;
    }

    return result;
}

// Функция для умножения строки числа на строку числа
string multiplyBigIntString(const string& num1, const string& num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int temp = (result[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            result[i + j + 1] = (temp % 10) + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }

    // Удаляем ведущие нули
    size_t startpos = result.find_first_not_of("0");
    if (startpos != string::npos) {
        return result.substr(startpos);
    }
    return "0";
}

// Функция для вычисления значения многочлена
string evaluatePolynomial(string* coefficients, int n, const string& x) {
    string result = "0";
    string power_of_x = "1"; // x^0 = 1

    for (int i = n; i >= 0; --i) {
        result = addBigInt(result, multiplyBigIntString(coefficients[i], power_of_x));
        if (i > 0) {
            power_of_x = multiplyBigIntString(power_of_x, x); // Переход к следующей степени
        }
    }

    return result;
}

// Функция для вывода многочлена в виде строки
void printPolynomial(string* coefficients, int n) {
    cout << "Многочлен: ";
    for (int i = 0; i <= n; ++i) {
        if (coefficients[i] == "0") continue;

        if (i > 0 && coefficients[i][0] != '-') {
            cout << " + ";
        } else if (coefficients[i][0] == '-') {
            cout << " - ";
            cout << coefficients[i].substr(1);
        }

        if (coefficients[i] != "1" || i == n) {
            cout << coefficients[i];
        }

        if (n - i > 0) {
            cout << "x";
            if (n - i > 1) {
                cout << "^(" << n - i << ")";
            }
        }
    }
    cout << endl;
}

