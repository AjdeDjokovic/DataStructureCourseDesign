#ifndef AOE_H
#define AOE_H

#define MAXN 1010
#define MAXM 10010

#include "edge.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <QString>
#include <QStringList>
#include <set>

class aoe
{
private:

    int n, m;
    int cnt;

    int length;

    int vertax[MAXN];

    int first[MAXN], topo[MAXN];
    int ind[MAXN], outd[MAXN];
    int tot;
    int Ee[MAXN], El[MAXN], E[MAXN], L[MAXN];

    Edge edge[MAXM];
    void dfs(int u,QString str);

public:
    QStringList list1; // 关键路径
    QStringList list2; //箭头排序
    aoe();
    void init();
    void set(int,std::set<int>);
    void read_graph(int u, int v, int w, int id);
    bool toposort();
    void CriticalPath();
    void dfs();
    QString outV(); // 结点
    QString outE();  // 活动
    int outLength();
    QString outTopo();
};

#endif // AOE_H
