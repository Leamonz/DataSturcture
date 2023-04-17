//
// Created by HP on 2022/11/30.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "MyList.h"
#include "MyQueue.h"
#include "MyStack.h"
#include <iostream>

const int DEFAULT_SIZE = 100;
const int INF = 1e8;
enum StatusCode {
    UnTraversed = 0,
    Traversed,
};

// 邻接表图顶点
template<class ElemType>
struct AdjListGraphVexNode {
    ElemType data{}; //元素值
    SimpleLinkList<int> *adjLink{};//邻接链表

    AdjListGraphVexNode();

    explicit AdjListGraphVexNode(ElemType d, SimpleLinkList<int> *adj = nullptr);

    AdjListGraphVexNode<ElemType> &operator=(const AdjListGraphVexNode<ElemType> &copy);
};

template<class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode() {
    adjLink = nullptr;
}

template<class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType d, SimpleLinkList<int> *adj) {
    data = d;
    adjLink = adj;
}

template<class ElemType>
AdjListGraphVexNode<ElemType> &AdjListGraphVexNode<ElemType>::operator=(const AdjListGraphVexNode<ElemType> &copy) {
    if (&copy != this) {
        this->data = copy.data;
        this->adjLink = copy.adjLink;
    }
    return *this;
}

// 有向图的邻接表
template<class ElemType>
class AdjListDirGraph {
protected:
    int vexNum{DEFAULT_SIZE}, edgeNum{0};
    AdjListGraphVexNode<ElemType> *vexTable;
    mutable StatusCode *tags; // 指向图中顶点标志的数组指针

    void DestroyHelp();

    int IndexHelp(const SimpleLinkList<int> *la, int v) const;//定位v在邻接表中的位置
public:
    explicit AdjListDirGraph(ElemType elems[], int vNum = DEFAULT_SIZE);

    explicit AdjListDirGraph(int vNum = DEFAULT_SIZE);

    ~AdjListDirGraph();

    bool GetElem(int v, ElemType &e) const;

    bool SetElem(int v, const ElemType &e);

    //ElemType GetInfinity() const;//返回无穷大？

    int GetVexNum() const;

    int GetEdgeNum() const;

    int FirstAdjVex(int v) const;//返回v的第一个邻接点

    int NextAdjVex(int v1, int v2) const;//返回v1相对于v2的下一个邻接点

    void InsertEdge(int v1, int v2);//插入以v1 v2为顶点的边

    void DeleteEdge(int v1, int v2);//删除边

    StatusCode GetTag(int v) const;

    void SetTag(int v, StatusCode t);

    AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);

    AdjListDirGraph<ElemType> &operator=(const AdjListDirGraph<ElemType> &copy);
};

template<class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const {
    return vexNum;
}

template<class ElemType>
int AdjListDirGraph<ElemType>::GetEdgeNum() const {
    return edgeNum;
}

template<class ElemType>
int AdjListDirGraph<ElemType>::IndexHelp(const SimpleLinkList<int> *la, int v) const {
    int curPos;
    int Vex;
    for (curPos = 1; curPos <= la->Length(); curPos++) {
        la->GetElem(curPos, Vex);
        if (Vex == v) break;
    }
    return curPos; // curPos = la->Length()+1 说明没有找到
}

template<class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const {
    if (v < 0 || v >= vexNum) {
//        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return -1;
    }
    if (vexTable[v].adjLink == nullptr) {
//        cout << "No Adjacent Vertexes" << endl;
        return -1;// 空邻接表，不存在邻接点
    } else {
        return vexTable[v].adjLink->GetElem(1);
    }
}

template<class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const {
    if (v1 < 0 || v1 >= vexNum) {
//        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return -1;
    } else if (v2 < 0 || v2 >= vexNum) {
//        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return -1;
    } else if (v1 == v2) {
//        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return -1;
    }
    if (vexTable[v1].adjLink == nullptr) {
//        cout << "No Adjacent Vertexes" << endl;
        return -1;// 空邻接表，不存在邻接点
    }
    int pos = IndexHelp(vexTable[v1].adjLink, v2);
    if (pos < vexTable[v1].adjLink->Length()) {
        return vexTable[v1].adjLink->GetElem(pos + 1);
    } else {
//        cout << v2 << " is the last adjacent vertex to " << v1 << endl;
        return -1;
    }
}

template<class ElemType>
bool AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const {
    if (v < 0 || v >= vexNum) {
//        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return false;
    } else {
        e = vexTable[v].data;
        return true;
    }
}

template<class ElemType>
bool AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e) {
    if (v < 0 || v >= vexNum) {
//        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return false;
    } else {
        vexTable[v].data = e;
        return true;
    }
}

template<class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= vexNum) {
//        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return;
    } else if (v2 < 0 || v2 >= vexNum) {
//        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return;
    } else if (v1 == v2) {
//        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return;
    }
    if (vexTable[v1].adjLink == nullptr)
        vexTable[v1].adjLink = new SimpleLinkList<int>;
    vexTable[v1].adjLink->Insert(vexTable[v1].adjLink->Length() + 1, v2);
}

template<class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= vexNum) {
//        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return;
    } else if (v2 < 0 || v2 >= vexNum) {
//        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return;
    } else if (v1 == v2) {
//        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return;
    }
    int pos = IndexHelp(vexTable[v1].adjLink, v2);
    vexTable[v1].adjLink->Delete(pos);
}

template<class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const {
    if (v < 0 || v >= vexNum) {
//        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
    }
    return tags[v];
}

template<class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode t) {
    if (v < 0 || v >= vexNum) {
//        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return;
    }
    tags[v] = t;
}

template<class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType *elems, int vNum) {
    vexNum = vNum;
    vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
    tags = new StatusCode[vexNum];
    for (int i = 0; i < vexNum; i++) {
        vexTable[i] = AdjListGraphVexNode<ElemType>(elems[i]);
        tags[i] = UnTraversed;
    }
}

template<class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vNum) {
    vexNum = vNum;
    vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
    tags = new StatusCode[vexNum];
}

template<class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &copy) {
    this->vexNum = copy.vexNum;
    this->edgeNum = copy.edgeNum;
    this->vexTable = new AdjListDirGraph<ElemType>[vexNum];
    this->tags = new StatusCode[vexNum];
    for (int i = 0; i < vexNum; i++) {
        this->vexTable[i] = copy.vexTable[i];
    }
}

template<class ElemType>
AdjListDirGraph<ElemType> &AdjListDirGraph<ElemType>::operator=(const AdjListDirGraph<ElemType> &copy) {
    if (&copy != this) {
        this->vexNum = copy.vexNum;
        this->edgeNum = copy.edgeNum;
        delete this->vexTable;
        delete this->tags;
        this->vexTable = new AdjListDirGraph<ElemType>[vexNum];
        this->tags = new StatusCode[vexNum];
        for (int i = 0; i < vexNum; i++) {
            this->vexTable[i] = copy.vexTable[i];
            this->tags[i] = UnTraversed;
        }
    }
    return *this;
}

template<class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp() {
    for (int i = 0; i < vexNum; i++) {
        if (vexTable[i].adjLink != nullptr)
            delete vexTable[i].adjLink;
    }
    delete vexTable;
}

template<class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph() {
    DestroyHelp();
}

// 有向网邻接表
template<class WeightType>
struct AdjListNetEdge {
    int vex;
    WeightType weight;

    AdjListNetEdge();

    AdjListNetEdge(int v, WeightType w);
};

template<class WeightType>
AdjListNetEdge<WeightType>::AdjListNetEdge() {
    vex = -1;
    weight = 0;
}

template<class WeightType>
AdjListNetEdge<WeightType>::AdjListNetEdge(int v, WeightType w) {
    vex = v;
    weight = w;
}

template<class ElemType, class WeightType>
struct AdjListNetVexNode {
    ElemType data;
    SimpleLinkList<AdjListNetEdge<WeightType>> *adjLink;

    AdjListNetVexNode();

    explicit AdjListNetVexNode(ElemType d, SimpleLinkList<AdjListNetEdge<WeightType>> *adj = nullptr);
};

template<class ElemType, class WeightType>
AdjListNetVexNode<ElemType, WeightType>::AdjListNetVexNode() {
    data = 0;
    adjLink = nullptr;
}

template<class ElemType, class WeightType>
AdjListNetVexNode<ElemType, WeightType>::AdjListNetVexNode(ElemType d,
                                                           SimpleLinkList<AdjListNetEdge<WeightType>> *adj) {
    data = d;
    adjLink = adj;
}

template<class ElemType, class WeightType>
class AdjListDirNet {
protected:
    int vexNum, edgeNum{0};
    AdjListNetVexNode<ElemType, WeightType> *vexTable;
    mutable StatusCode *tags;
    WeightType infinity;

    void DestroyHelp();

    int IndexHelp(const SimpleLinkList<AdjListNetEdge<WeightType>> *la, int v) const;

public:
    explicit AdjListDirNet(ElemType elems[], int vNum = DEFAULT_SIZE, WeightType inf = INF);

    explicit AdjListDirNet(int vNum = DEFAULT_SIZE, WeightType inf = INF);

    ~AdjListDirNet();

    bool GetElem(int v, ElemType &e) const;

    bool SetElem(int v, ElemType &e);

    WeightType GetInfinity() const;

    int GetVexNum() const;

    int GetEdgeNum() const;

    int FirstAdjVex(int v) const;

    int NextAdjVex(int v1, int v2) const;

    void InsertEdge(int v1, int v2, WeightType w);

    void DeleteEdge(int v1, int v2);

    bool GetWeight(int v1, int v2, WeightType &w) const;

    bool SetWeight(int v1, int v2, WeightType &w);

    bool GetTag(int v, StatusCode &code) const;

    bool SetTag(int v, StatusCode &code);

    AdjListDirNet(const AdjListDirNet<ElemType, WeightType> &copy);

    AdjListDirNet<ElemType, WeightType> &operator=(const AdjListDirNet<ElemType, WeightType> &copy);
};

template<class ElemType, class WeightType>
int AdjListDirNet<ElemType, WeightType>::IndexHelp(const SimpleLinkList<AdjListNetEdge<WeightType>> *la, int v) const {
    int pos;
    for (pos = 1; pos <= la->Length(); pos++) {
        if (v == la->GetElem(pos))
            return pos;
    }
    return pos;
}

template<class ElemType, class WeightType>
bool AdjListDirNet<ElemType, WeightType>::GetElem(int v, ElemType &e) const {
    if (v < 0 || v >= vexNum) {
        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return false;
    }
    e = vexTable[v].data;
    return true;
}

template<class ElemType, class WeightType>
bool AdjListDirNet<ElemType, WeightType>::SetElem(int v, ElemType &e) {
    if (v < 0 || v >= vexNum) {
        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return false;
    }
    vexTable[v].data = e;
    return true;
}

template<class ElemType, class WeightType>
WeightType AdjListDirNet<ElemType, WeightType>::GetInfinity() const {
    return infinity;
}

template<class ElemType, class WeightType>
int AdjListDirNet<ElemType, WeightType>::GetEdgeNum() const {
    return edgeNum;
}

template<class ElemType, class WeightType>
int AdjListDirNet<ElemType, WeightType>::GetVexNum() const {
    return vexNum;
}

template<class ElemType, class WeightType>
int AdjListDirNet<ElemType, WeightType>::FirstAdjVex(int v) const {
    if (v < 0 || v >= vexNum) {
        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return -1;
    }
    if (vexTable[v].adjLink == nullptr) {
        cout << "No Adjacent Vertexes" << endl;
        return -1;
    }
    return vexTable[v].adjLink->GetElem(1).vex;
}

template<class ElemType, class WeightType>
int AdjListDirNet<ElemType, WeightType>::NextAdjVex(int v1, int v2) const {
    if (v1 < 0 || v1 >= vexNum) {
        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return -1;
    } else if (v2 < 0 || v2 >= vexNum) {
        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return -1;
    } else if (v1 == v2) {
        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return -1;
    }
    int pos = IndexHelp(vexTable[v1].adjLink, v2);
    if (pos < vexTable[v1].adjLink->Length()) {
        return vexTable[v1].adjLink->GetElem(pos + 1).vex;
    } else {
        cout << v2 << " is the last adjacent vertex to " << v1 << endl;
        return -1;
    }
}

template<class ElemType, class WeightType>
void AdjListDirNet<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w) {
    if (v1 < 0 || v1 >= vexNum) {
        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return;
    } else if (v2 < 0 || v2 >= vexNum) {
        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return;
    } else if (v1 == v2) {
        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return;
    }
    vexTable[v1].adjLink->Insert(AdjListNetEdge<WeightType>(v2, w));
}

template<class ElemType, class WeightType>
void AdjListDirNet<ElemType, WeightType>::DeleteEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= vexNum) {
        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return;
    } else if (v2 < 0 || v2 >= vexNum) {
        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return;
    } else if (v1 == v2) {
        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return;
    }
    int pos = IndexHelp(vexTable[v1].adjLink, v2);
    vexTable[v1].adjLink->Delete(pos);
}

template<class ElemType, class WeightType>
bool AdjListDirNet<ElemType, WeightType>::GetWeight(int v1, int v2, WeightType &w) const {
    if (v1 < 0 || v1 >= vexNum) {
        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return -1;
    } else if (v2 < 0 || v2 >= vexNum) {
        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return -1;
    } else if (v1 == v2) {
        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return -1;
    }
    int pos = IndexHelp(vexTable[v1].adjLink, v2);
    w = vexTable[v1].adjLink->GetElem(pos).weight;
    return true;
}

template<class ElemType, class WeightType>
bool AdjListDirNet<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType &w) {
    if (v1 < 0 || v1 >= vexNum) {
        cout << "v1 should be in range[" << 0 << "," << vexNum - 1 << "] but v1=" << v1 << endl;
        return -1;
    } else if (v2 < 0 || v2 >= vexNum) {
        cout << "v2 should be in range[" << 0 << "," << vexNum - 1 << "] but v2=" << v2 << endl;
        return -1;
    } else if (v1 == v2) {
        cout << "v1 can't be equal to v2, but get v1=" << v1 << ", v2=" << v2 << endl;
        return -1;
    }
    int pos = IndexHelp(vexTable[v1].adjLink, v2);
    vexTable[v1].adjLink->GetElem(pos).weight = w;
    return true;
}

template<class ElemType, class WeightType>
bool AdjListDirNet<ElemType, WeightType>::GetTag(int v, StatusCode &code) const {
    if (v < 0 || v >= vexNum) {
        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return false;
    }
    code = tags[v];
    return true;
}

template<class ElemType, class WeightType>
bool AdjListDirNet<ElemType, WeightType>::SetTag(int v, StatusCode &code) {
    if (v < 0 || v >= vexNum) {
        cout << "v should be in range[" << 0 << "," << vexNum - 1 << "] but v=" << v << endl;
        return false;
    }
    tags[v] = code;
    return true;
}

template<class ElemType, class WeightType>
AdjListDirNet<ElemType, WeightType>::AdjListDirNet(ElemType *elems, int vNum, WeightType inf) {
    INF = inf;
    vexNum = vNum;
    vexTable = new AdjListNetVexNode<ElemType, WeightType>[vexNum];
    tags = new StatusCode[vexNum];
    for (int v = 0; v < vexNum; v++) {
        vexTable[v].data = AdjListGraphVexNode<ElemType>(elems[v]);
    }
}

template<class ElemType, class WeightType>
AdjListDirNet<ElemType, WeightType>::AdjListDirNet(int vNum, WeightType inf) {
    INF = inf;
    vexNum = vNum;
    vexTable = new AdjListNetVexNode<ElemType, WeightType>[vexNum];
    tags = new StatusCode[vexNum];
}

template<class ElemType, class WeightType>
AdjListDirNet<ElemType, WeightType>::AdjListDirNet(const AdjListDirNet<ElemType, WeightType> &copy) {
    this->vexNum = copy.vexNum;
    this->edgeNum = copy.edgeNum;
    vexTable = new AdjListNetVexNode<ElemType, WeightType>[vexNum];
    tags = new StatusCode[vexNum];
    for (int v = 0; v < copy.GetVexNum(); v++) {
        vexTable[v] = copy[v];
    }
}

template<class ElemType, class WeightType>
AdjListDirNet<ElemType, WeightType> &
AdjListDirNet<ElemType, WeightType>::operator=(const AdjListDirNet<ElemType, WeightType> &copy) {
    if (&copy != this) {
        this->vexNum = copy.vexNum;
        this->edgeNum = copy.edgeNum;
        if (vexTable != nullptr) delete vexTable;
        if (tags != nullptr) delete tags;
        vexTable = new AdjListNetVexNode<ElemType, WeightType>[vexNum];
        tags = new StatusCode[vexNum];
        for (int v = 0; v < copy.GetVexNum(); v++) {
            vexTable[v] = copy[v];
        }
    }
    return *this;
}

template<class ElemType, class WeightType>
void AdjListDirNet<ElemType, WeightType>::DestroyHelp() {
    for (int v = 0; v < GetVexNum(); v++) {
        if (vexTable[v].adjLink != nullptr)
            delete vexTable[v].adjLink;
    }
    delete vexTable;
}

template<class ElemType, class WeightType>
AdjListDirNet<ElemType, WeightType>::~AdjListDirNet() {
    DestroyHelp();
}

template<class ElemType>
void DFS(const AdjListDirGraph<ElemType> &graph, int v, void (*visit)(ElemType &)) {
    int curVex = v;
    ElemType elem;
    graph.GetElem(curVex, elem);
    visit(curVex);
    graph.SetTag(curVex, Traversed);
    for (curVex = graph.FirstAdjVex(curVex); curVex >= 0; curVex = graph.NextAdjVex(v, curVex)) {
        if (graph.GetTag(curVex) == UnTraversed) {
            DFS(graph, curVex, visit);
        }
    }
}

template<class ElemType>
void DFSTraverse(const AdjListDirGraph<ElemType> &graph, void (*visit)(ElemType &)) {
    for (int v = 0; v < graph.GetVexNum(); v++) {
        graph.SetTag(v, UnTraversed);
    }
    for (int v = 0; v < graph.GetVexNum(); v++) {
        if (graph.GetTag(v) == UnTraversed) {
            DFS(graph, v, visit);
        }
    }
}

template<class ElemType>
void BFS(const AdjListDirGraph<ElemType> &graph, int v, void(*visit)(ElemType &)) {
    LinkQueue<ElemType> q;
    q.PushBack(v);
    int w, curVex;
    ElemType elem;
    while (!q.Empty()) {
        q.PopFront(curVex);
        if (graph.GetTag(curVex) == UnTraversed) {
            graph.GetElem(v, elem);
            visit(elem);
            graph.SetTag(curVex, Traversed);
            for (w = graph.FirstAdjVex(curVex); w >= 0; w = graph.NextAdjVex(curVex, w)) {
                graph.GetElem(w, elem);
                visit(elem);
                graph.SetTag(w, Traversed);
            }
        }
    }
}

template<class ElemType>
void BFSTraverse(const AdjListDirGraph<ElemType> &graph, void(*visit)(ElemType &)) {
    for (int v = 0; v < graph.GetVexNum(); v++) {
        graph.SetTag(v, UnTraversed);
    }
    for (int curVex = 0; curVex < graph.GetVexNum(); curVex++) {
        if (graph.GetTag(curVex) == UnTraversed) {
            BFS(graph, curVex, visit);
        }
    }
}

template<class ElemType>
void CountInDegrees(const AdjListDirGraph<ElemType> &graph, int *&inDeg) {
    for (int v = 0; v < graph.GetVexNum(); v++) {
        for (int w = graph.FirstAdjVex(v); w >= 0; w = graph.NextAdjVex(v, w)) {
            inDeg[w]++;
        }
    }
}

template<class ElemType>
bool TopologicalSort(const AdjListDirGraph<ElemType> &graph, LinkStack<int> *TopRes = nullptr) {
    // 拓扑排序，用于判断有向图中是否存在环
    int *inDeg = new int[graph.GetVexNum()];
    LinkQueue<int> q;
    int count = 0;
    CountInDegrees(graph, inDeg); // 统计每个顶点的入度
    for (int v = 0; v < graph.GetVexNum(); v++) {
        graph.SetTag(v, UnTraversed);
        if (inDeg[v] == 0) {
            cout << v << " ";
            q.PushBack(v);
            count++;
        }
    }

    while (!q.Empty()) {
        int v = q.PopFront();
        if (TopRes != nullptr) TopRes->Push(v);//保存拓扑排序的逆序列
        graph.SetTag(v, Traversed);
        for (int w = graph.FirstAdjVex(v); w >= 0; w = graph.NextAdjVex(v, w)) {
            if (graph.GetTag(w) == Traversed) continue;
            inDeg[w]--;
            if (inDeg[w] == 0) {
                cout << w << " ";
                q.PushBack(w);
                count++;
            }
        }
    }
    delete[] inDeg;
    cout << endl;
    return count != graph.GetVexNum();//如果count!=graph.GetVexNum() 那么说明图中存在环
}

#endif //DATASTRUCTURE_GRAPH_H
