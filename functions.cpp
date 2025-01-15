#include "header.h"

// Функция для проверки, является ли степень многочлена натуральным числом
int inputDegree() {
    int n;
    cout << "Введите степень многочлена (неотрицательное число n): ";
    while (true) {
        cin >> n;

        if (cin.fail() || n < 0) {
            cout << "Ошибка! Введите неотрицательное целое число (n >= 0): ";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            return n;
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
            if (!isdigit(c) && c != '-' && c != '+') {
                cout << "Ошибка! Коэффициент должен быть целым числом. Повторите ввод." << endl;
                --i; // Повторяем ввод для текущего коэффициента
                break;
            }
        }
    }
}

// Функция для удаления ведущих нулей из числа
string removeLeadingZeros(const string& num) {
    size_t startpos = num.find_first_not_of("0");
    if (startpos == string::npos) return "0";
    return num.substr(startpos);
}

// Функция для умножения двух больших чисел в строковом представлении
string multiplyBigIntString(const string& num1, const string& num2) {
    bool isNegative = (num1[0] == '-' ? 1 : 0) ^ (num2[0] == '-' ? 1 : 0);
    string n1 = (num1[0] == '-' ? num1.substr(1) : num1);
    string n2 = (num2[0] == '-' ? num2.substr(1) : num2);

    int len1 = n1.size();
    int len2 = n2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int temp = (result[i + j + 1] - '0') + (n1[i] - '0') * (n2[j] - '0') + carry;
            result[i + j + 1] = (temp % 10) + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }

    result = removeLeadingZeros(result);
    return isNegative && result != "0" ? "-" + result : result;
}

// Функция для сложения двух больших чисел
string addBigInt(const string& num1, const string& num2) {
    if (num1[0] == '-' && num2[0] == '-') {
        return "-" + addBigInt(num1.substr(1), num2.substr(1));
    } else if (num1[0] == '-') {
        return addBigInt(num2, "-" + num1.substr(1));
    } else if (num2[0] == '-') {
        return addBigInt(num1, "-" + num2.substr(1));
    }

    string result = "";
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? (num1[i--] - '0') : 0;
        int digit2 = (j >= 0) ? (num2[j--] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        result = char((sum % 10) + '0') + result;
        carry = sum / 10;
    }

    return removeLeadingZeros(result);
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
    bool firstTerm = true;

    for (int i = 0; i <= n; ++i) {
        if (coefficients[i] == "0") continue;

        if (!firstTerm) {
            if (coefficients[i][0] != '-') {
                cout << " + ";
            } else {
                cout << " ";
            }
        }

        if (coefficients[i] != "1" && coefficients[i] != "-1") {
            cout << coefficients[i];
        } else if (coefficients[i] == "-1" && (n - i > 0)) {
            cout << "-";
        } else if (coefficients[i] == "1" && (n - i > 0)) {
            // Пропускаем вывод "1" перед x
        } else {
            cout << coefficients[i];
        }

        if (n - i > 0) {
            cout << "x";
            if (n - i > 1) {
                cout << "^(" << n - i << ")";
            }
        }

        firstTerm = false;
    }

    cout << endl;
}

