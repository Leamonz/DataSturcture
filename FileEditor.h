//
// Created by HP on 2022/10/17.
//

#ifndef UTILS_HPP_FILEEDITOR_H
#define UTILS_HPP_FILEEDITOR_H

#include "MyString.h"
#include "MyList.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

class Editor {
private:
    BiLinkList<CharString> StringBuffer;
    int curLineNo{0};
//    int tarLineNo{0};
//    CharString Line{""};
    char userCommand{'?'};
    ifstream inFile;
    ofstream outFile;
public:
    bool UserSaysYes();

    void NextLine();

    void PreviousLine();

    void GotoLine(int tarLineNo);

    void InsertLine(int LineNo, const CharString &newLine);

    void ChangeLine(int LineNo, const CharString &newLine);

    void DeleteLine(int LineNo);

    void ReadFile();

    void WriteFile();

    void FindCharString(const CharString &tarLine);

    void View();//查看（显示）缓冲区

    void ShowLine(int num);//显示当前行

    // i(insert), e(end), q(quit), d(delete), g(goto), v(view), ?/h(help), n(next)
    // p(prior), b(begin), r(read), w(write), c(change)
    char GetCommand();

    void RunCommand(char ch);

    void Run();
};

void Editor::Run() {
    char infName[255] = "", outfName[255] = "";
    cout << "输入文件名(缺省:file_in.txt):" << endl;
    strcpy(infName, Read(cin).CStr());
    if (strlen(infName) == 0) {
        strcpy(infName, "file_in.txt");
    }

    cout << "输出文件名(缺省:file_out.txt):" << endl;
    strcpy(outfName, Read(cin).CStr());
    if (strlen(outfName) == 0) {
        strcpy(outfName, "file_out.txt");
    }
    inFile.open(infName, ios::in);
    outFile.open(outfName, ios::out | ios::app);
    if (inFile.fail()) {
        cout << "没有以下文件: " << infName << endl;
        exit(1);
    }
    if (outFile.fail()) {
        cout << "输出文件打开失败" << endl;
        exit(2);
    }
    ReadFile();
    while ((userCommand = GetCommand()) != 'q') {
        RunCommand(userCommand);
    }
    RunCommand('q');
    inFile.close();
    outFile.close();
}

char Editor::GetCommand() {
    if (curLineNo == 0) {
        cout << "? ";
    } else {
        cout << "\n当前所在行: ";
        ShowLine(curLineNo);
        cout << "?";
//        CharString curLine = StringBuffer.GetElem(curLineNo);
//        cout << curLineNo << ": " << curLine << endl << "? ";
    }
    cin >> userCommand;
    userCommand = tolower(userCommand);
    while (cin.get() != '\n');  // 忽略用户输入的其他符号
    return userCommand;
}

void Editor::RunCommand(char ch) {
    int tarLineNo;
    CharString Line;
    switch (ch) {
        case 'b':
            if (StringBuffer.Empty()) {
                cout << "缓存为空" << endl;
            } else {
                GotoLine(1);
            }
            break;
        case 'e':
            if (StringBuffer.Empty()) {
                cout << "缓存为空" << endl;
            } else {
                GotoLine(StringBuffer.Length());
            }
            break;
        case 'q':
            cout << "程序结束！" << endl;
            char ch;
            cout << "是否将缓存区内容保存到目的文件中?(Y/N): ";
            ch = cin.get();
            if (tolower(ch) == 'y') {
                cout << "缓存区内容已经写入目的文件！" << endl;
                WriteFile();
            }
            break;
        case 'd':
            cout << "请输入要删除的行数: ";
            cin >> tarLineNo;
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length()) {
                cout << "输入错误！" << endl;
            } else {
                DeleteLine(tarLineNo);
                cout << "删除第" << tarLineNo << "行成功" << endl;
            }
            break;
        case 'i':
            cout << "请输入要在哪一行插入: ";
            cin >> tarLineNo;
            getchar();
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length() + 1) {
                cout << "输入错误！" << endl;
            } else {
                cout << "请输入插入的文本: ";
                Line = Read(cin);
                InsertLine(tarLineNo, Line);
            }
            break;
        case 'c':
            cout << "请输入要修改的行数: ";
            cin >> tarLineNo;
            getchar();
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length()) {
                cout << "输入错误！" << endl;
            } else {
                cout << "请输入修改后的文本: ";
                Line = Read(cin);
                ChangeLine(tarLineNo, Line);
            }
            break;
        case 'g':
            cout << "请输入要跳转的行数: ";
            cin >> tarLineNo;
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length()) {
                cout << "输入错误！" << endl;
            } else {
                GotoLine(tarLineNo);
            }
            break;
        case 'v':
            View();
            break;
        case 'r':
            ReadFile();
            break;
        case 'w':
            WriteFile();
            break;
        case 'f':
            cout << "请输入要查找的内容: ";
            Line = Read(cin);
            FindCharString(Line);
            break;
        case 'n':
            if (curLineNo == StringBuffer.Length()) {
                cout << "已经是最后一行" << endl;
            } else {
                NextLine();
            }
            break;
        case 'p':
            if (curLineNo == 0) {
                cout << "已经是第一行" << endl;
            } else {
                PreviousLine();
            }
            break;
        case '?':
        case 'h':
            cout << "有效指令：" << endl;
            cout << "b(begin), e(end), i(insert), d(delete), c(change), g(goto), " << endl;
            cout << "v(view), r(read), w(write), ?/h(help), n(next), p(prior)" << endl;
        default:
            cout << "可以输入?/h以获取帮助" << endl;
            break;
    }
}

void Editor::ShowLine(int num) {
    CharString curLine;
    StringBuffer.GetElem(num, curLine);
    cout << num << ": " << curLine << endl;
}

bool Editor::UserSaysYes() {
    cout << "是否确定退出？(Y/N): ";
    char op;
    cin >> op;
    op = toupper(op);
    while (cin.get() != '\n');
    if (op == 'Y') {
        // 将缓存区内容写入文件
        WriteFile();
        return true;
    } else {
        return false;
    }
}

void Editor::NextLine() {
    curLineNo++;
    ShowLine(curLineNo);
}

void Editor::PreviousLine() {
    curLineNo--;
    ShowLine(curLineNo);
}

void Editor::GotoLine(int tarLineNo) {
    curLineNo = tarLineNo;
    ShowLine(curLineNo);
}

void Editor::InsertLine(int LineNo, const CharString &newLine) {
    curLineNo = LineNo;
    StringBuffer.Insert(curLineNo, newLine);
    cout << "插入行成功！ ";
    ShowLine(curLineNo);
}

void Editor::ChangeLine(int LineNo, const CharString &newLine) {
    curLineNo = LineNo;
    StringBuffer.SetElem(curLineNo, newLine);
    ShowLine(curLineNo);
}

void Editor::DeleteLine(int LineNo) {
    curLineNo = LineNo - 1;
    StringBuffer.Delete(LineNo);
}

void Editor::View() {
    if (StringBuffer.Length() == 0) {
        cout << "当前缓存为空" << endl;
    } else {
        cout << "当前缓存如下: " << endl;
        for (int i = 1; i <= StringBuffer.Length(); i++) {
            ShowLine(i);
        }
    }
}

void Editor::WriteFile() {
    CharString Line;
    for (int i = 1; i <= StringBuffer.Length(); i++) {
        StringBuffer.GetElem(i, Line);
        outFile << Line << endl;
    }
    cout << "已将缓存区内容输出到指定文件中！" << endl;
}

void Editor::ReadFile() {
    CharString Line;
    inFile.clear();
    inFile.seekg(0);
    Line = Read(inFile);
    StringBuffer.Insert(StringBuffer.Length() + 1, Line);
    while (!inFile.eof()) {
        Line = Read(inFile);
        if (!Line.Empty()) {
            StringBuffer.Insert(StringBuffer.Length() + 1, Line);
        }
    }
}

void Editor::FindCharString(const CharString &tarLine) {
    CharString Line, res;
    int count = 0;
    for (int i = 1; i <= StringBuffer.Length(); i++) {
        StringBuffer.GetElem(i, Line);
        int t = Line.search(tarLine, res);
        if (t) {
            cout << i << ": " << res << endl;
            count += t;
        }
    }
    if (!count) {
        cout << "没有找到目标内容" << endl;
    } else {
        cout << "一共找到" << count << "处符合的内容" << endl;
    }
}

#endif //UTILS_HPP_FILEEDITOR_H
