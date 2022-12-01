//
// Created by HP on 2022/11/30.
//

#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H

#include "MyList.h"
#include <iostream>

const int DEFAULT_SIZE = 100;

// 邻接表图顶点
template<class ElemType>
struct AdjListGraphVexNode {
    ElemType data; //元素值
    SimpleLinkList<int> *adjLink;//邻接链表

    AdjListGraphVexNode();

    explicit AdjListGraphVexNode(ElemType d, SimpleLinkList<int> *adj = nullptr);
};

template<class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode() {
    data = 0;
    adjLink = nullptr;
}

template<class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType d, SimpleLinkList<int> *adj) {
    data = d;
    adjLink = adj;
}

// 有向图的邻接表
template<class ElemType>
class AdjListDirGraph {
protected:
    int vexNum, edgeNum;
    AdjListGraphVexNode<ElemType> *vexTable;

    void DestroyHelp();

    int IndexHelp(const SimpleLinkList<int> *la, int v) const;//定位v在邻接表中的位置
public:
    AdjListDirGraph(ElemType elems[], int vNum = DEFAULT_SIZE);

    AdjListDirGraph(int vNum = DEFAULT_SIZE);

    ~AdjListDirGraph();

    bool GetElem(int v, ElemType &e) const;

    bool SetElem(int v, const ElemType &e);

    ElemType GetInfinity() const;//返回无穷大？

    int GetVexNum() const;

    int GetEdgeNum() const;

    int FirstAdjVex(int v) const;//返回v的第一个邻接点

    int NextAdjVex(int v1, int v2) const;//返回v1相对于v2的下一个邻接点

    void InsertEdge(int v1, int v2);//插入以v1 v2为顶点的边

    void DeleteEdge(int v1, int v2);//删除边

    AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);

    AdjListDirGraph<ElemType> &operator=(const AdjListDirGraph<ElemType> &copy);
};

#endif //UNTITLED_GRAPH_H
