//
// Created by HP on 2022/9/17.
//
#include<iostream>
#include"MyStack.h"

using namespace std;
//const char operators[7] = {'+', '-', '*', '/', '(', ')', '='};
//
//bool Find(char theta) {
//    for (char op: operators) {
//        if (theta == op) {
//            return true;
//        }
//    }
//    return false;
//}
//
//class Calculator {
//private:
//    static bool isOperator(char theta);//判断是否为操作符
//    static char Precede(char theta1, char theta2);//计算两个操作符的优先级
//    static double Operate(double left, char theta, double right);//计算 left theta right 的值并返回
//    static void Get2Operands(LinkStack<double> &opnd, double &left, double &right);//返回两个操作数
//public:
//    Calculator() = default;
//
//    virtual ~Calculator() = default;
//
//    static void Run();//运行程序
//};
//
//bool Calculator::isOperator(char theta) {
//    return Find(theta);
//}
//
//void Calculator::Get2Operands(LinkStack<double> &opnd, double &left, double &right) {
//    left = opnd.Pop();
//    right = opnd.Pop();
//}
//
//double Calculator::Operate(double left, char theta, double right) {
//    switch (theta) {
//        case '+':
//            return left + right;
//        case '-':
//            return left - right;
//        case '*':
//            return left * right;
//        case '/':
//            return left / right;
//        default:
//            cout << "运算符错误" << endl;
//            exit(1);
//    }
//}
//
//char Calculator::Precede(char theta1, char theta2) {
//    if ((theta1 == '(' && theta2 == ')') || (theta1 == '=' && '=' == theta2)) {
//        return '=';
//    }
//    if ((theta1 == '(' && theta2 == '=') || (theta1 == ')' && theta2 == '(') || (theta1 == '=' && theta2 == ')')) {
//        return 'e';
//    }
//    if ((theta1 == theta2) || ((theta1 == '*' || theta1 == '/') && theta2 != '(') || theta1 == ')') {
//        return '>';
//    }
//    if (theta1 == '(' || theta1 == '=' || theta2 == '(' || (theta2 == '*' || theta2 == '/')) {
//        return '<';
//    }
//}
//
//void Calculator::Run() {
//    LinkStack<double> opnd;//operands
//    LinkStack<char> optr;//operators
//    optr.Push('=');
//    char ch;
//    char optrTop;
//    double operand;
//    char theta;
//
//    cin >> ch;
//    while ((optrTop = optr.GetHead(), optrTop != '=') && (ch != '=')) {
//        if (isOperator(ch)) {
//            switch (Precede(optrTop, ch)) {
//                case '<':
//                    optr.Push(ch);
//                    cin >> ch;
//                    break;
//                case '=':
//                    optrTop = optr.Pop();//脱括号
//                    cin >> ch;
//                    break;
//                case '>':
//                    double left, right;
//                    Get2Operands(opnd, left, right);
//                    theta = optr.Pop();
//                    opnd.Push(Operate(left, theta, right));
//                    break;
//                case 'e':
//                    cout << "操作符匹配错误" << endl;
//                    exit(2);
//                default:
//                    break;
//            }
//        } else {
//            cin.putback(ch);//如果不是运算符则将字符ch返回输入流
//            cin >> operand;
//            opnd.Push(operand);
//            cin >> ch;
//        }
//    }
//    double result = opnd.Pop();
//    cout << "表达式的值为：" << result << endl;
//}
//
//int main() {
//    Calculator calc;
//    calc.Run();
//    return 0;
//}

