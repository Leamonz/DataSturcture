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

    void Write(unsigned int bit);//��Ŀ���ļ�д��һ��bit
    void WriteToOutfp();//ǿ��д��Ŀ���ļ�
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
        // ���û�����
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
    cout << "���ڴ������Ժ�..." << endl;

    map<char, unsigned long> mp;
    unsigned long size = 0;
    infp.clear();//�����ļ�ָ�뵱ǰλ��
    infp.seekg(0);//�ļ�ָ��ָ���ļ���ʼλ��
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
        //��ʼ���ַ����鼰��Ȩ��
        ch[n] = it.first;
        w[n] = it.second;
        size += w[n++];
    }
    pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);
    outfp.clear();
    outfp.seekp(0);//�ļ�ָ��ָ���ļ���ʼλ��

    outfp.write((char *) &size, sizeof(unsigned long));//��Ŀ���ļ�д��Դ�ļ��Ĵ�С
    outfp.write((char *) &n, sizeof(unsigned int));//д���ַ�����
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
    cout << "�������!" << endl;
}

void HuffmanCompress::Unzip() {
    cout << "���ڴ������Ժ�..." << endl;

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
            //�ж����λΪ0/1
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
        if (len == size) break;//��ѹ���
        infp.read(&cha, sizeof(char));
    }

    infp.close();
    outfp.close();
    delete pHuffmanTree;
    cout << "�������!" << endl;
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
            cout << "������ѹ���ļ�: ";
            cin >> inFile;
            cin.get();
            infp.open(inFile.c_str(), ios::in | ios::binary);
            if (infp.fail()) {
                cout << "ERROR: Դ�ļ���ʧ��!" << endl;
                return true;
            }
            infp.get();
            if (infp.eof()) {
                cout << "ERROR: Դ�ļ�Ϊ��!" << endl;
                return true;
            }
            cout << "������Ŀ���ļ�: ";
            cin >> outFile;
            cin.get();
            outfp.open(outFile.c_str(), ios::out | ios::binary);
            start = clock();
            Zip();
            end = clock();
            cout << "ѹ���ļ���ʹ��: " << (end - start) / CLOCKS_PER_SEC << "��" << endl;
            return true;
        case 2:
            cout << "�������ѹ�ļ�: ";
            cin >> inFile;
            infp.open(inFile.c_str(), ios::in | ios::binary);
            if (infp.fail()) {
                cout << "ERROR: Դ�ļ���ʧ��!" << endl;
                return true;
            }
            infp.get();
            if (infp.eof()) {
                cout << "ERROR: Դ�ļ�Ϊ��!" << endl;
                return true;
            }
            cout << "������Ŀ���ļ�: ";
            cin >> outFile;
            cin.get();
            outfp.open(outFile.c_str(), ios::out | ios::binary);
            start = clock();
            Unzip();
            end = clock();
            cout << "��ѹ�ļ���ʹ��: " << (end - start) / CLOCKS_PER_SEC << "��" << endl;
            return true;
        case 3:
            cout << "�˳�����!" << endl;
            return false;
        default:
            cout << "�������������ѡ��" << endl;
            return true;
    }
}

void HuffmanCompress::Menu() {
    cout << "=====================" << endl;
    cout << "      1.ѹ���ļ�" << endl;
    cout << "      2.��ѹ�ļ�" << endl;
    cout << "        3.�˳�" << endl;
    cout << "=====================" << endl;
}


#endif //UNTITLED_HUFFMANCOMPRESS_H
