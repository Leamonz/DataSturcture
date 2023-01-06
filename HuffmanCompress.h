//
// Created by HP on 2022/11/28.
//

#ifndef UNTITLED_HUFFMANCOMPRESS_H
#define UNTITLED_HUFFMANCOMPRESS_H

#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>

using namespace std;
struct BufferType {
    char ch;
    unsigned int bits;
};


class HuffmanCompress {
protected:
    HuffmanTree<char, unsigned long> *pHuffmanTree{};
    ifstream infp;
    ofstream outfp;
    BufferType buf{0, 0};

    void Write(unsigned int bit);//向目标文件写入一个bit
    void WriteToOutfp();//强制写入目标文件
public:
    HuffmanCompress() = default;

    ~HuffmanCompress() = default;

    static void Menu();

    void Zip();

    void Unzip();

    bool Run();
};

void HuffmanCompress::Write(unsigned int bit) {
    buf.bits++;
    buf.ch = (buf.ch << 1) | bit;
    if (buf.bits == 8) {
        outfp.write(&buf.ch, 1);
        // 重置缓存区
        buf.bits = 0;
        buf.ch = 0;
    }
}

void HuffmanCompress::WriteToOutfp() {
    unsigned int len = buf.bits;
    if (len > 0) {
        for (unsigned int i = 0; i < 8 - len; i++) {
            Write(0);
        }
    }
}

void HuffmanCompress::Zip() {
    cout << "正在处理，请稍候..." << endl;

    map<char, unsigned long> mp;
    unsigned long size = 0;
    infp.clear();//清理文件指针当前位置
    infp.seekg(0);//文件指针指向文件起始位置
    char cha;
    infp.read(&cha, sizeof(char));
    int temp = 0;
    while (!infp.eof()) {
        if (mp.find(cha) != mp.end()) {
            mp[cha]++;
        } else {
            temp++;
            mp[cha] = 1;
        }
        infp.read(&cha, sizeof(char));
    }
    char ch[temp];
    unsigned long w[temp];
    unsigned int n = 0;
    for (auto &it: mp) {
        //初始化字符数组及其权重
        ch[n] = it.first;
        w[n] = it.second;
        size += w[n++];
    }
    pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);
    outfp.clear();
    outfp.seekp(0);//文件指针指向文件起始位置

    outfp.write((char *) &size, sizeof(unsigned long));//向目标文件写入源文件的大小
    outfp.write((char *) &n, sizeof(unsigned int));//写入字符个数
    outfp.write(ch, n);
    outfp.write((char *) w, sizeof(unsigned long) * n);
    buf.bits = 0;
    buf.ch = 0;
    infp.clear();
    infp.seekg(0);
    infp.read(&cha, sizeof(char));
    while (!infp.eof()) {
        CharString strCode = pHuffmanTree->Encode(cha);
        for (unsigned int i = 0; i < strCode.Length(); i++) {
            if (strCode[i] == '0') Write(0);
            else Write(1);
        }
        infp.read(&cha, sizeof(char));
    }
    WriteToOutfp();

    infp.close();
    outfp.close();
    delete pHuffmanTree;
    cout << "处理结束!" << endl;
}

void HuffmanCompress::Unzip() {
    cout << "正在处理，请稍候..." << endl;

    unsigned int n, len = 0;
    unsigned long size;
    infp.clear();
    infp.seekg(0);
    infp.read((char *) &size, sizeof(unsigned long));
    infp.read((char *) &n, sizeof(unsigned int));
    char ch[n];
    unsigned long w[n];
    infp.read(ch, n);
    infp.read((char *) w, sizeof(unsigned long) * n);
    pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);
    char cha;
    outfp.clear();
    outfp.seekp(0);
    infp.read(&cha, sizeof(char));
    while (!infp.eof()) {
        CharString strTemp("");
        unsigned char c = (unsigned char) cha;
        for (unsigned int i = 0; i < 8; i++) {
            //判断最高位为0/1
            if (c < 128) Concat(strTemp, CharString("0"));
            else Concat(strTemp, CharString("1"));
            c = c << 1;
        }
        CharString str = pHuffmanTree->Decode(strTemp);
        for (unsigned int i = 0; i < str.Length(); i++) {
            len++;
            outfp.write(&str[i], sizeof(char));
            if (len == size) break;
        }
        if (len == size) break;//解压完毕
        infp.read(&cha, sizeof(char));
    }

    infp.close();
    outfp.close();
    delete pHuffmanTree;
    cout << "处理结束!" << endl;
}

bool HuffmanCompress::Run() {
    int choice;
    Menu();
    cin >> choice;
    cin.get();
    string inFile;
    string outFile;
    clock_t start, end;
    switch (choice) {
        case 1:
            cout << "请输入压缩文件: ";
            cin >> inFile;
            cin.get();
            infp.open(inFile.c_str(), ios::in | ios::binary);
            if (infp.fail()) {
                cout << "ERROR: 源文件打开失败!" << endl;
                return true;
            }
            infp.get();
            if (infp.eof()) {
                cout << "ERROR: 源文件为空!" << endl;
                return true;
            }
            cout << "请输入目标文件: ";
            cin >> outFile;
            cin.get();
            outfp.open(outFile.c_str(), ios::out | ios::binary);
            start = clock();
            Zip();
            end = clock();
            cout << "压缩文件共使用: " << (end - start) / CLOCKS_PER_SEC << "秒" << endl;
            return true;
        case 2:
            cout << "请输入解压文件: ";
            cin >> inFile;
            infp.open(inFile.c_str(), ios::in | ios::binary);
            if (infp.fail()) {
                cout << "ERROR: 源文件打开失败!" << endl;
                return true;
            }
            infp.get();
            if (infp.eof()) {
                cout << "ERROR: 源文件为空!" << endl;
                return true;
            }
            cout << "请输入目标文件: ";
            cin >> outFile;
            cin.get();
            outfp.open(outFile.c_str(), ios::out | ios::binary);
            start = clock();
            Unzip();
            end = clock();
            cout << "解压文件共使用: " << (end - start) / CLOCKS_PER_SEC << "秒" << endl;
            return true;
        case 3:
            cout << "退出程序!" << endl;
            return false;
        default:
            cout << "输入错误，请重新选择" << endl;
            return true;
    }
}

void HuffmanCompress::Menu() {
    cout << "=====================" << endl;
    cout << "      1.压缩文件" << endl;
    cout << "      2.解压文件" << endl;
    cout << "        3.退出" << endl;
    cout << "=====================" << endl;
}


#endif //UNTITLED_HUFFMANCOMPRESS_H
