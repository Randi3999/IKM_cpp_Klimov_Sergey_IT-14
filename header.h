#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
using namespace std;

// Объявления функций
int inputDegree();
void inputCoefficients(string* coefficients, int n);
string multiplyBigInt(const string& num, int x);
string addBigInt(const string& num1, const string& num2);
string multiplyBigIntString(const string& num1, const string& num2);
string evaluatePolynomial(string* coefficients, int n, const string& x);
void printPolynomial(string* coefficients, int n);

#endif // HEADER_H

