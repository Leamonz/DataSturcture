//
// Created by HP on 2022/10/1.
//
//#include "Node.hpp"
//#include "SingleLinkedList.hpp"
//#include<iostream>

//using namespace std;

//int main() {
//    SingleLinkedList<int> test;
//    for (int i = 0; i < 5; i++) {
//        test.insert(i + 1, test.length());
//    }
//    int elem;
//    for (int i = 0; i < 5; i++) {
//        test.get(i, elem);
//        cout << elem << ' ';
//    }
//    cout << endl;
////    test.deleteElem(4);
////    test.deleteElem(3);
////    test.deleteElem(2);
////    test.deleteElem(1);
////    test.get(0, elem);
////    cout << elem << endl;
////    test.deleteElem(0);
//    cout << test.empty() << endl;
////    test.clear();
////    cout << test.empty() << endl;
//    cout << test[100];
//    return 0;
//}

//#include <iostream>                         // ������������ӿ��ļ�
//using namespace std;
//int main()                                  // ����������
//{                                           // ��������ʼ
//    char choice;                            // ģ��ţ��ַ���
//    int nChoice;                            // ģ��ţ����֣�
//    system("cls");
//    cout<<"\n\n\n\n\n";
//    cout<<"\t\t|---------------ѧ��ѡ��ϵͳ(ѧ����)------------|\n";
//    cout<<"\t\t|\t 0. ����                               |\n";
//    cout<<"\t\t|\t 1. ѧ����Ϣ����                       |\n";
//    cout<<"\t\t|\t 2. ��ʦ��Ϣ��Ϣ                       |\n";
//    cout<<"\t\t|\t 3. �γ���Ϣ����                       |\n";
//    cout<<"\t\t|\t 4. ѧ��ѡ����Ϣ                       |\n";
//    cout<<"\t\t|\t 5. ѧ���ɼ�����                       |\n";
//    cout<<"\t\t|\t 6. ��Ϣͳ��ģ��                       |\n";
//    cout<<"\t\t|-----------------------------------------------|\n\n";
//    cout<<"\t\t\t������ģ����(0-6):";
//    cin>>choice;                            // �����ַ�ģ���
//    if(choice < '0' || choice > '9')        // �����ģ��Ų�������
//      {
//          cout<<"ģ���ӦΪ���֣�"<<endl;
//          return 1;                          // ģ��Ų���ȷ�����ش������
//      }
//    nChoice = choice - '0';                // ���ַ�ģ���תΪ����
//    switch(nChoice)
//    {
//        case 0:
//            cout<<"�������ģ������Ϊ��0. ����"<<endl;
//            break;
//        case 1:
//            cout<<"�������ģ������Ϊ��1. ѧ����Ϣ����"<<endl;
//            break;
//        case 2:
//            cout<<"�������ģ������Ϊ��2. ��ʦ��Ϣ��Ϣ"<<endl;
//            break;
//        case 3:
//            cout<<"�������ģ������Ϊ��3. �γ���Ϣ����"<<endl;
//            break;
//        case 4:
//            cout<<"�������ģ������Ϊ��4. ѧ��ѡ����Ϣ"<<endl;
//            break;
//        case 5:
//            cout<<"�������ģ������Ϊ��5. ѧ���ɼ�����"<<endl;
//            break;
//        case 6:
//            cout<<"�������ģ������Ϊ��6. ��Ϣͳ��ģ��"<<endl;
//            break;
//        default:
//            cout<<"�������ģ�鲻���ڣ�"<<endl;
//    }
//    return 0;
//}                                           // ����������
