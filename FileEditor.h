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

    void View();//�鿴����ʾ��������

    void ShowLine(int num);//��ʾ��ǰ��

    // i(insert), e(end), q(quit), d(delete), g(goto), v(view), ?/h(help), n(next)
    // p(prior), b(begin), r(read), w(write), c(change)
    char GetCommand();

    void RunCommand(char ch);

    void Run();
};

void Editor::Run() {
    char infName[255] = "", outfName[255] = "";
    cout << "�����ļ���(ȱʡ:file_in.txt):" << endl;
    strcpy(infName, Read(cin).CStr());
    if (strlen(infName) == 0) {
        strcpy(infName, "file_in.txt");
    }

    cout << "����ļ���(ȱʡ:file_out.txt):" << endl;
    strcpy(outfName, Read(cin).CStr());
    if (strlen(outfName) == 0) {
        strcpy(outfName, "file_out.txt");
    }
    inFile.open(infName, ios::in);
    outFile.open(outfName, ios::out | ios::app);
    if (inFile.fail()) {
        cout << "û�������ļ�: " << infName << endl;
        exit(1);
    }
    if (outFile.fail()) {
        cout << "����ļ���ʧ��" << endl;
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
        cout << "\n��ǰ������: ";
        ShowLine(curLineNo);
        cout << "?";
//        CharString curLine = StringBuffer.GetElem(curLineNo);
//        cout << curLineNo << ": " << curLine << endl << "? ";
    }
    cin >> userCommand;
    userCommand = tolower(userCommand);
    while (cin.get() != '\n');  // �����û��������������
    return userCommand;
}

void Editor::RunCommand(char ch) {
    int tarLineNo;
    CharString Line;
    switch (ch) {
        case 'b':
            if (StringBuffer.Empty()) {
                cout << "����Ϊ��" << endl;
            } else {
                GotoLine(1);
            }
            break;
        case 'e':
            if (StringBuffer.Empty()) {
                cout << "����Ϊ��" << endl;
            } else {
                GotoLine(StringBuffer.Length());
            }
            break;
        case 'q':
            cout << "���������" << endl;
            char ch;
            cout << "�Ƿ񽫻��������ݱ��浽Ŀ���ļ���?(Y/N): ";
            ch = cin.get();
            if (tolower(ch) == 'y') {
                cout << "�����������Ѿ�д��Ŀ���ļ���" << endl;
                WriteFile();
            }
            break;
        case 'd':
            cout << "������Ҫɾ��������: ";
            cin >> tarLineNo;
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length()) {
                cout << "�������" << endl;
            } else {
                DeleteLine(tarLineNo);
                cout << "ɾ����" << tarLineNo << "�гɹ�" << endl;
            }
            break;
        case 'i':
            cout << "������Ҫ����һ�в���: ";
            cin >> tarLineNo;
            getchar();
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length() + 1) {
                cout << "�������" << endl;
            } else {
                cout << "�����������ı�: ";
                Line = Read(cin);
                InsertLine(tarLineNo, Line);
            }
            break;
        case 'c':
            cout << "������Ҫ�޸ĵ�����: ";
            cin >> tarLineNo;
            getchar();
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length()) {
                cout << "�������" << endl;
            } else {
                cout << "�������޸ĺ���ı�: ";
                Line = Read(cin);
                ChangeLine(tarLineNo, Line);
            }
            break;
        case 'g':
            cout << "������Ҫ��ת������: ";
            cin >> tarLineNo;
            if (tarLineNo < 0 || tarLineNo > StringBuffer.Length()) {
                cout << "�������" << endl;
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
            cout << "������Ҫ���ҵ�����: ";
            Line = Read(cin);
            FindCharString(Line);
            break;
        case 'n':
            if (curLineNo == StringBuffer.Length()) {
                cout << "�Ѿ������һ��" << endl;
            } else {
                NextLine();
            }
            break;
        case 'p':
            if (curLineNo == 0) {
                cout << "�Ѿ��ǵ�һ��" << endl;
            } else {
                PreviousLine();
            }
            break;
        case '?':
        case 'h':
            cout << "��Чָ�" << endl;
            cout << "b(begin), e(end), i(insert), d(delete), c(change), g(goto), " << endl;
            cout << "v(view), r(read), w(write), ?/h(help), n(next), p(prior)" << endl;
        default:
            cout << "��������?/h�Ի�ȡ����" << endl;
            break;
    }
}

void Editor::ShowLine(int num) {
    CharString curLine;
    StringBuffer.GetElem(num, curLine);
    cout << num << ": " << curLine << endl;
}

bool Editor::UserSaysYes() {
    cout << "�Ƿ�ȷ���˳���(Y/N): ";
    char op;
    cin >> op;
    op = toupper(op);
    while (cin.get() != '\n');
    if (op == 'Y') {
        // ������������д���ļ�
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
    cout << "�����гɹ��� ";
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
        cout << "��ǰ����Ϊ��" << endl;
    } else {
        cout << "��ǰ��������: " << endl;
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
    cout << "�ѽ����������������ָ���ļ��У�" << endl;
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
        cout << "û���ҵ�Ŀ������" << endl;
    } else {
        cout << "һ���ҵ�" << count << "�����ϵ�����" << endl;
    }
}

#endif //UTILS_HPP_FILEEDITOR_H
