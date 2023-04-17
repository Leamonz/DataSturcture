//
// Created by HP on 2022/11/26.
//

#ifndef DATASTRUCTURE_CALCULATOR_H
#define DATASTRUCTURE_CALCULATOR_H

#include "MyStack.h"
#include<iostream>
#include<cmath>

using namespace std;

double fact(double n) {
    double res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

int book[128] = {0};

const char precede[9][9] = {
        '>', '>', '<', '<', '<', '>', '>', '<', '<',
        '>', '>', '<', '<', '<', '>', '>', '<', '<',
        '>', '>', '>', '>', '<', '>', '>', '<', '<',
        '>', '>', '>', '>', '<', '>', '>', '<', '<',
        '<', '<', '<', '<', '<', '=', 'e', '<', '<',
        '>', '>', '>', '>', 'e', '>', '>', '>', '>',
        '<', '<', '<', '<', '<', 'e', '=', '<', '<',
        '>', '>', '>', '>', '<', '>', '>', '>', '>',
        '>', '>', '>', '>', '<', '>', '>', '>', '>'
};

class Calculator {
public:
    static bool IsOperator(char ch);

    static char Precede(char theta1, char theta2);

    static double Operate(double left, char theta, double right);

    static double Operate(double left, char theta);

    static void Get2Operands(LinkStack<double> &opnd, double &left, double &right);

    static void Get1Operand(LinkStack<double> &opnd, double &left);


    Calculator() = default;

    virtual ~Calculator() = default;

    static void Run();
};

bool Calculator::IsOperator(char ch) {
    return ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')' || ch == '=' || ch == '^' ||
           ch == '!';
}

double Calculator::Operate(double left, char theta, double right) {
    double res = 0;
    switch (theta) {
        case '+':
            res = left + right;
            break;
        case '-':
            res = left - right;
            break;
        case '*':
            res = left * right;
            break;
        case '/':
            if (right == 0) {
                cout << "除数不能为0!" << endl;
                exit(2);
            }
            res = left / right;
            break;
        case '^':
            res = pow(left, right);
            break;
        default:
            break;
    }
    return res;
}

double Calculator::Operate(double left, char theta) {
    double res = 0;
    switch (theta) {
        case '!':
            res = fact(left);
        default:
            break;
    }
    return res;
}

void Calculator::Get2Operands(LinkStack<double> &opnd, double &left, double &right) {
    right = opnd.Pop();
    left = opnd.Pop();
}

void Calculator::Get1Operand(LinkStack<double> &opnd, double &left) {
    left = opnd.Pop();
}

char Calculator::Precede(char theta1, char theta2) {
    return precede[book[theta1]][book[theta2]];
}

void Calculator::Run() {
    book['+'] = 0, book['-'] = 1, book['*'] = 2, book['/'] = 3, book['('] = 4,
    book[')'] = 5, book['='] = 6, book['^'] = 7, book['!'] = 8;
    LinkStack<double> opnd;
    LinkStack<char> optr;
    char optrTop, ch;
    optr.Push('=');
    double operand, left, right, res;
    char theta;
    cin >> ch;
    while ((optr.Top(optrTop), optrTop != '=') || ch != '=') {
        if (IsOperator(ch)) {
            char com = Precede(optrTop, ch);
            switch (com) {
                case '<':
                    optr.Push(ch);
                    cin >> ch;
                    break;
                case '='://操作符为左右括号
                    optrTop = optr.Pop();
                    cin >> ch;
                    break;
                case '>':
                    theta = optr.Pop();//optrTop
                    if (theta == '!') {
                        Get1Operand(opnd, left);
                        res = Operate(left, theta);
                    } else {
                        Get2Operands(opnd, left, right);
                        res = Operate(left, theta, right);
                    }
                    opnd.Push(res);
                    break;
                case 'e':
                    cout << "操作数匹配错误" << endl;
                    exit(1);
                default:
                    break;
            }
        } else {
            cin.putback(ch);
            cin >> operand;
            opnd.Push(operand);
            cin >> ch;
        }
    }
    res = opnd.Pop();
    cout << res << endl;
}

#endif //DATASTRUCTURE_CALCULATOR_H
