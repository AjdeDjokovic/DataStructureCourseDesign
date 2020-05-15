#include "aoe.h"

aoe::aoe()
{
    init();
}

void aoe::set(int m,std::set<int> s)
{
    this->n = s.size();
    this->m = m;
    int i = 0;
    for(std::set<int>::iterator iter = s.begin();iter != s.end();iter++)
        vertax[i++] = *iter;
}

void aoe::init()
{
    cnt = 0;
    tot = 0;
    length = 0;
    memset(first, -1, sizeof(first));
    memset(ind, 0, sizeof(ind));
    memset(outd, 0, sizeof(outd));
    memset(Ee, 0, sizeof(Ee));
    memset(E, 0, sizeof(E));
    memset(L, 0, sizeof(L));
}

void aoe::read_graph(int u, int v, int w, int id)
{
    edge[cnt].v = v, edge[cnt].w = w, edge[cnt].id = id;
    edge[cnt].next = first[u], first[u] = cnt++; //first 最新出边
    outd[u]++;
    ind[v]++;
}

bool aoe::toposort()
{
    std::queue<int> q;
    for(int i = 0; i < n; i++) if(!ind[vertax[i]]) q.push(vertax[i]);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        topo[++tot] = x;
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, w = edge[e].w;
            if(--ind[v] == 0) q.push(v);
            if(Ee[v] < Ee[x] + w) //求出各个顶点Ee值
            {
                Ee[v] = Ee[x] + w;
            }
        }
    }
    if(tot == n)
        return true;
    else
        return false;
}

void aoe::CriticalPath()
{
    int top = tot;
    for(int i = 0; i < n; i++) El[vertax[i]] = Ee[topo[tot]]; //初始化顶点事件的最迟发生时间
    while(top) //逆拓扑排序求顶点El的值
    {
        int x = topo[top--];
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, w = edge[e].w;
            if(El[x] > El[v] - w)
            {
                El[x] = El[v] - w;
            }
        }
    }
    for(int u = 0; u < n; u++) //求出E,L关键活动
    {
        for(int e = first[u]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, id = edge[e].id, w = edge[e].w; //id代表活动的标号
            E[id] = Ee[u];
            L[id] = El[v] - w;
            if(E[id] == L[id]) //相等一定是关键活动
            {
                QString str = "activity" + QString::number(id) + " : " + QString::number(u) +"-->" + QString::number(v) + "\n";
                list1.append(str);//sprintf("a%d : %d->%d\n", id, u, v);
            }
        }
    }
}


void aoe::dfs()
{
    dfs(topo[1],"");
}

void aoe::dfs(int u,QString str)
{
    if(u == topo[tot])
        {
            str += QString::number(u) + "\n";
            list2.append(str);
            return;
        }
        str += QString::number(u) + "-->";
        for(int e = first[u]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, id = edge[e].id, w = edge[e].w; //id代表活动的标号
            E[id] = Ee[u], L[id] = El[v] - w;
            if (E[id] == L[id]) //相等一定是关键活动
            {
                dfs(v,str);
            }
        }
}

QString aoe::outV()
{
    QString str = "vertex\t\tearly\t\tlast\n";
    for(int i = 1;i <= tot;i++)
        str += "vtx" + QString::number(topo[i]) + "\t\t" + QString::number(Ee[topo[i]]) + "\t\t" + QString::number(El[topo[i]]) + "\n";
    return str;
}

QString aoe::outE()
{
    QString str = "activity\t\tearly\t\tlast\n";
    for(int i = 1;i <= m;i++)
        str += "act" + QString::number(i) + "\t\t" + QString::number(E[i]) + "\t\t" + QString::number(L[i]) + "\n";
    return str;
}

int aoe::outLength()
{
    length = 0;
    int cur = topo[1];
    for(int i = 1; i <= n; i++) //求出E,L关键活动
    {
        int u = topo[i];
        if(cur != u)
            continue;
        for(int e = first[u]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, id = edge[e].id, w = edge[e].w;   //id代表活动的标号
            if(E[id] == L[id]) //相等一定是关键活动
            {
                cur = v;
                length += w;
                break;
            }
        }
    }
    return length;
}

QString aoe::outTopo()
{
    QString str;
    for(int i = 1;i <= tot;i++)
        str += QString::number(topo[i]) + "\t";
    str += "\n\n";
    return str;
}
