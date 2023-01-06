//
// Created by HP on 2022/9/17.
//
#include<iostream>
#include"../MyStack.h"

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
//    static bool isOperator(char theta);//�ж��Ƿ�Ϊ������
//    static char Precede(char theta1, char theta2);//�������������������ȼ�
//    static double Operate(double left, char theta, double right);//���� left theta right ��ֵ������
//    static void Get2Operands(LinkStack<double> &opnd, double &left, double &right);//��������������
//public:
//    Calculator() = default;
//
//    virtual ~Calculator() = default;
//
//    static void Run();//���г���
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
//            cout << "���������" << endl;
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
//                    optrTop = optr.Pop();//������
//                    cin >> ch;
//                    break;
//                case '>':
//                    double left, right;
//                    Get2Operands(opnd, left, right);
//                    theta = optr.Pop();
//                    opnd.Push(Operate(left, theta, right));
//                    break;
//                case 'e':
//                    cout << "������ƥ�����" << endl;
//                    exit(2);
//                default:
//                    break;
//            }
//        } else {
//            cin.putback(ch);//���������������ַ�ch����������
//            cin >> operand;
//            opnd.Push(operand);
//            cin >> ch;
//        }
//    }
//    double result = opnd.Pop();
//    cout << "���ʽ��ֵΪ��" << result << endl;
//}
//
//int main() {
//    Calculator calc;
//    calc.Run();
//    return 0;
//}

