//
// Created by HP on 2022/12/17.
//

#ifndef MAIN_CPP_SCHEDULE_H
#define MAIN_CPP_SCHEDULE_H

#include "MyString.h"
#include "Graph.h"
#include "MyStack.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

const char *DecimalToChinese[11] =
        {"", "一", "二", "三", "四", "五",
         "六", "七", "八", "九", "十"};

struct CourseType {
    CharString courseNo{"None"}; // 课程编号
    CharString courseName{"None"};// 课程名
    int period{0};// 学时数
    int term{0};// 开课学期

    CourseType() = default;

    CourseType(CharString num, CharString name, int p, int t);
};

CourseType::CourseType(CharString num, CharString name, int p, int t) {
    courseNo = num;
    courseName = name;
    period = p;
    term = t;
}


template<int termsNum>
class Schedule {
protected:
    AdjListDirGraph<CourseType> *pGraph{};
    int *inDeg{};
    ifstream infp;
    ofstream outfp;
    LinkQueue<int> q[termsNum + 1];// 入度为0的结点的缓冲队列
    char coursesTable[termsNum + 1][11][6][100]{};// 课表， 下标分别表示学期、节次、星期、课程名
    int coursesNumPerTerm[termsNum + 1]{};// 每学期的课程数
    CharString inFile, outFile;

    // 辅助函数
    int LocateVex(const CharString &courseNum);// 返回编号为courseNum的课程在图中的位置

    void Range(int num, int term, const CharString &name);// 排课

    bool RangeOne(int &weekday, int term, const CharString &name);// 排一天的1节课

    bool RangeTwo(int &weekday, int term, const CharString &name);// 排一天的2节课

    bool RangeThree(int &weekday, int term, const CharString &name);// 排一天的3节课

    int FindOneVacant(int weekday, int term);// 查找一天1节空课

    int FindTwoVacant(int weekday, int term);// 查找一天连续2节空课

    int FindThreeVacant(int weekday, int term);// 查找一天连续3节空课

    CharString DecimalToChineseChar(int n);// 用中文表示十进制数

    char GetChar(istream &in);// 从输入流中跳过空格及制表符获取一个字符

    void CreateSchedule(const CharString &in_file, const CharString &out_file);

public:
    Schedule(CharString inFile, CharString outFile);

    virtual ~Schedule();

    void TopologicalOrder();

    void Write();

};

template<int termsNum>
int Schedule<termsNum>::LocateVex(const CharString &courseNum) {
    CourseType courseV;
    for (int v = 0; v < pGraph->GetVexNum(); v++) {
        pGraph->GetElem(v, courseV);
        if (courseV.courseNo == courseNum) {
            return v;
        }
    }
    cout << "没有找到编号为" << courseNum << "的课程!" << endl;
    return -1;// 没有找到对应编号的课程
}

template<int termsNum>
CharString Schedule<termsNum>::DecimalToChineseChar(int n) {
    return CharString(DecimalToChinese[n]);
}

template<int termsNum>
char Schedule<termsNum>::GetChar(istream &in) {
    char ch;
    ch = in.get();
    while (ch == ' ' || ch == '\t') {
        ch = in.get();
    }
    return ch;
}

template<int termsNum>
void Schedule<termsNum>::Range(int num, int term, const CharString &name) {
    int weekday = 1;
    int haveClass[6] = {};// 不在同一天重复排课
    bool flag_3 = false, flag_2 = false, flag_1 = false;
    while (num != 0) {
        if (haveClass[weekday] == 1) continue;
        if (num >= 3) {
            int temp = weekday;
            do {
                flag_3 = RangeThree(weekday, term, name);
                weekday += 1;
            } while (!flag_3 && weekday != temp);
            if (!flag_3) {
                flag_2 = RangeTwo(weekday, term, name);
                if (!flag_2) {
                    weekday += 1;
                    continue;
                }
                flag_1 = RangeOne(weekday, term, name);
                if (!flag_1) {
                    haveClass[weekday] = 1;
                    num -= 2;
                    weekday = (weekday + 2 > 5) ? ((weekday + 2) % 5) : (weekday + 2);
                    continue;
                }
            }
            // 排了三节课
            haveClass[weekday] = 1;
            num -= 3;
            weekday = (weekday + 1 > 5) ? ((weekday + 1) % 5) : (weekday + 1);
        } else if (num == 2) {
            flag_2 = RangeTwo(weekday, term, name);
            if (!flag_2) {
                weekday += 1;
                continue;
            }
            num -= 2;
        } else {
            flag_1 = RangeOne(weekday, term, name);
            if (!flag_1) {
                weekday += 1;
                continue;
            }
            num -= 1;
        }
    }
}

template<int termsNum>
bool Schedule<termsNum>::RangeOne(int &weekday, int term, const CharString &name) {
    int pos = FindOneVacant(weekday, term);
    if (pos == -1)
        return false;
    else {
        strcpy(coursesTable[term][pos][weekday], name.CStr());
        return true;
    }
}

template<int termsNum>
bool Schedule<termsNum>::RangeTwo(int &weekday, int term, const CharString &name) {
    int pos = FindTwoVacant(weekday, term);
    if (pos == -1)
        return false;
    else {
        for (int i = 0; i < 2; i++) {
            strcpy(coursesTable[term][pos + i][weekday], name.CStr());
        }
        return true;
    }
}

template<int termsNum>
bool Schedule<termsNum>::RangeThree(int &weekday, int term, const CharString &name) {
    int pos = FindThreeVacant(weekday, term);
    if (pos == -1)
        return false;
    else {
        for (int i = 0; i < 3; i++) {
            strcpy(coursesTable[term][pos + i][weekday], name.CStr());
        }
        return true;
    }
}

template<int termsNum>
int Schedule<termsNum>::FindOneVacant(int weekday, int term) {
    for (int i = 1; i <= 10; i++) {
        if (strcmp(coursesTable[term][i][weekday], "") == 0)
            return i;
    }
    return -1;
}

template<int termsNum>
int Schedule<termsNum>::FindTwoVacant(int weekday, int term) {
    if (strcmp(coursesTable[term][1][weekday], "") == 0
        && strcmp(coursesTable[term][2][weekday], "") == 0) {
        return 1;
    } else if (strcmp(coursesTable[term][6][weekday], "") == 0
               && strcmp(coursesTable[term][7][weekday], "") == 0) {
        return 6;
    } else {
        for (int pos = 3; pos < 5; pos++) {
            int j = 0;
            while (strcmp(coursesTable[term][pos + j][weekday], "") == 0) {
                j++;
                if (j == 2)
                    return pos;
            }
        }
        for (int pos = 8; pos < 10; pos++) {
            int j = 0;
            while (strcmp(coursesTable[term][pos + j][weekday], "") == 0) {
                j++;
                if (j == 2)
                    return pos;
            }
        }
    }
    return -1;
}

template<int termsNum>
int Schedule<termsNum>::FindThreeVacant(int weekday, int term) {
    if (strcmp(coursesTable[term][3][weekday], "") == 0
        && strcmp(coursesTable[term][4][weekday], "") == 0
        && strcmp(coursesTable[term][5][weekday], "") == 0) {
        return 3;
    } else if (strcmp(coursesTable[term][8][weekday], "") == 0
               && strcmp(coursesTable[term][9][weekday], "") == 0
               && strcmp(coursesTable[term][10][weekday], "") == 0) {
        return 8;
    }
    return -1;
}

template<int termsNum>
void Schedule<termsNum>::CreateSchedule(const CharString &in_file, const CharString &out_file) {
    inFile = in_file;
    outFile = out_file;
    infp.open(inFile.CStr(), ios::in);
    if (infp.fail()) {
        cout << "源文件打开失败!" << endl;
        exit(1);
    }
    infp.get();
    if (infp.eof()) {
        cout << "源文件为空!" << endl;
        exit(2);
    }
    infp.clear();
    infp.seekg(0);
    outfp.open(outFile.CStr(), ios::out);
    if (outfp.fail()) {
        cout << "保存文件打开失败!" << endl;
        exit(3);
    }
    outfp.close();
    infp >> coursesNumPerTerm[1];
    int vexNum = coursesNumPerTerm[1];
    for (int i = 2; i <= termsNum; i++) {
        infp >> coursesNumPerTerm[i];
        vexNum += coursesNumPerTerm[i];
    }
    infp.get();
    pGraph = new AdjListDirGraph<CourseType>(vexNum);
    inDeg = new int[vexNum]{};
    CourseType courseV, courseW;
    // 需要使用string。c风格字符串和CharString在输入的时候都会报错
    string num, name, preCourseNum;
    int p, t;
    char ch;
    int v = 0;
    infp >> num;
    infp >> name;
    infp >> p;
    infp >> t;
    pGraph->SetElem(v++, CourseType(CharString(num.c_str()), CharString(name.c_str()), p, t));
    while (true) {
        infp >> num;
        infp >> name;
        infp >> p;
        infp >> t;
        pGraph->SetElem(v, CourseType(CharString(num.c_str()), CharString(name.c_str()), p, t));
        ch = infp.get();
        if (infp.eof())
            break;
        while (ch != '\n') {
            // 读取先修课程(如果有)
            infp.putback(ch);
            infp >> preCourseNum;
            int w = LocateVex(CharString(preCourseNum.c_str()));
            pGraph->InsertEdge(w, v);
            inDeg[v] += 1;
            ch = infp.get();
        }
        v++;
    }
    if (v != vexNum) {
        cout << "错误！课程总数与要求不符!" << endl;
        exit(11);
    }
    infp.close();
}

template<int termsNum>
Schedule<termsNum>::Schedule(CharString inFile, CharString outFile) {
    CreateSchedule(inFile, outFile);
}

template<int termsNum>
Schedule<termsNum>::~Schedule() {
    delete pGraph;
    delete[] inDeg;
}

template<int termsNum>
void Schedule<termsNum>::TopologicalOrder() {
    CourseType courseV, courseW;
    int i, size0, sizeTerm, term, v, w;
    for (v = 0; v < pGraph->GetVexNum(); v++) {
        if (inDeg[v] == 0) {
            pGraph->GetElem(v, courseV);
            q[courseV.term].PushBack(v);
        }
    }
    // 生成课表
    for (term = 1; term < termsNum; term++) {
        size0 = q[0].Length();
        sizeTerm = q[term].Length();
        if (size0 + sizeTerm < coursesNumPerTerm[term] || sizeTerm > coursesNumPerTerm[term]) {
            cout << "term: " << term << endl;
            cout << "size0: " << size0 << endl;
            cout << "sizeTerm: " << sizeTerm << endl;
            cout << "coursesNumPerTerm: " << coursesNumPerTerm[term] << endl;
            cout << "排课时出现冲突!" << endl;
            exit(4);
        }

        for (i = 1; i <= sizeTerm; i++) {
            v = q[term].PopFront();
            pGraph->GetElem(v, courseV);
            Range(courseV.period, term, courseV.courseName);
            for (w = pGraph->FirstAdjVex(v); w != -1; w = pGraph->NextAdjVex(v, w)) {
                inDeg[w]--;
                pGraph->GetElem(w, courseW);
                if (inDeg[w] == 0 && (courseW.term == 0 || courseW.term > term)) {
                    q[courseW.term].PushBack(w);
                } else if (inDeg[w] == 0 && (courseW.term > 0 && courseW.term <= term)) {
                    cout << "排课时出现冲突!" << endl;
                    exit(5);
                }
            }
        }
        for (i = 1; i <= coursesNumPerTerm[term] - sizeTerm; i++) {
            v = q[0].PopFront();
            pGraph->GetElem(v, courseV);
            Range(courseV.period, term, courseV.courseName);
            for (w = pGraph->FirstAdjVex(v); w != -1; w = pGraph->NextAdjVex(v, w)) {
                inDeg[w]--;
                pGraph->GetElem(w, courseW);
                if (inDeg[w] == 0 && (courseW.term == 0 || courseW.term > term)) {
                    q[courseW.term].PushBack(w);
                } else if (inDeg[w] == 0 && (courseW.term > 0 && courseW.term <= term)) {
                    cout << "排课时出现冲突!" << endl;
                    exit(6);
                }
            }
        }
    }
}

template<int termsNum>
void Schedule<termsNum>::Write() {
    for (int i = 1; i <= termsNum; i++) {
        outfp.open(outFile.CStr(), ios::in | ios::app);
        outfp << "第" << DecimalToChineseChar(i) << "学期课表\r\n";
        outfp << setw(18) << setiosflags(ios::left) << "节次" << setw(18) << "星期一" << setw(18)
              << "星期二" << setw(18) << "星期三" << setw(18) << "星期四" << "星期五\r\n";
        for (int j = 1; j <= 10; j++) {
            string day = string("第") + string(DecimalToChineseChar(j).CStr()) + string("节");
            outfp << setiosflags(ios::left) << setw(18) << day;
            for (int k = 1; k <= 5; k++) {
                outfp << setiosflags(ios::left) << setw(18) << coursesTable[i][j][k] << " ";
            }
            outfp << "\n";
            if (j == 2 || j == 7) {
                outfp << "\n" << "课间休息" << "\n\n";
            } else if (j == 5) {
                outfp << "\n" << "午间休息" << "\n\n";
            } else if (j == 10) {
                outfp << "\n" << "晚自习" << "\n\n\n\n";
            }
        }
        outfp.close();
    }
    cout << "排课完成，已将排课结果写入文件\"" << outFile << "\"中" << endl;
}

#endif //MAIN_CPP_SCHEDULE_H
