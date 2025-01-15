#include "header.h"

int main() {
    // Ввод степени многочлена
    int n = inputDegree();

    // Создание массива для коэффициентов
    string* coefficients = new string[n + 1];

    // Ввод коэффициентов
    inputCoefficients(coefficients, n);

    // Ввод значения x
    string x;
    cout << "Введите значение x: ";
    cin >> x;

    // Проверка корректности значения x
    for (char c : x) {
        if (!isdigit(c) && c != '-') {
            cout << "Ошибка! x должно быть целым числом." << endl;
            delete[] coefficients;
            return 1;
        }
    }

    // Вывод многочлена
    printPolynomial(coefficients, n);

    // Вычисление значения многочлена
    string result = evaluatePolynomial(coefficients, n, x);

    // Вывод результата
    cout << "Значение многочлена: " << result << endl;

    // Освобождение памяти
    delete[] coefficients;

    return 0;
}

