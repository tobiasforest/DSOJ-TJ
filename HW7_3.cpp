#if defined(__GNUC__)
#include <bits/stdc++.h>
#elif defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <ctime>
#include <iomanip>
#include <queue>
#endif

#define inf INT_MAX
using namespace std;

struct ArcNode
{
    int adjvex = -1;
    int weight = 0;
    ArcNode *nextarc = nullptr;
}; // struct ArcNode

typedef int VertexType;
struct VNode
{
    VertexType data = 0;
    ArcNode *firstarc = nullptr;
}; // struct VNode

enum GraphType
{
    UNDEFINED, // Undefined
    DG,        // Directed Graph
    DN,        // Undirected Graph
    UDG,       // Directed Network
    UDN        // Undirected Network
};
istream &operator>>(istream &in, GraphType &e)
{
    int ie;
    in >> ie;
    e = (GraphType)ie;
    return in;
}

class ALGraph
{
protected:
    GraphType type;
    int vexNum = 0;
    int arcNum = 0;
    VNode *vertices = nullptr; // pointer to vertices
    int *visited = nullptr;
    inline bool isNetwork() const { return type == DN || type == UDN; }
    inline bool isUndirected() const { return type == UDG || type == UDN; }
    int locateV(const int value)
    {
        int v = -1;
        for (int i = 0; i < vexNum; i++)
        {
            if (value == vertices[i].data)
            {
                v = i;
                break;
            }
        }
        return v;
    }
    ArcNode *locateA(const int n, const int value)
    {
        if (-1 == n)
        {
            return nullptr;
        }
        ArcNode *cur = vertices[n].firstarc;
        while (cur)
        {
            int v = locateV(value);

            if (v == cur->adjvex)
            {
                break;
            }
            cur = cur->nextarc;
        }
        return cur;
    }
    ArcNode *firstAdjVex(const int c)
    {
        return c >= vexNum ? nullptr : vertices[c].firstarc;
    }
    ArcNode *nextAdjVex(const int v, const int w)
    {
        ArcNode *cur = firstAdjVex(v);
        int i = 0;
        while (cur && ++i <= w)
        {
            cur = cur->nextarc;
        }
        return cur;
    }

    void dfs(const int v, int (ALGraph::*visit)(int))
    {
        visited[v] = 1;
        (this->*visit)(v);

        int cnt = 0;
        for (ArcNode *w = firstAdjVex(v); w; w = nextAdjVex(v, cnt))
        {
            if (!visited[w->adjvex])
            {
                cout << " ";
                dfs(w->adjvex, visit);
            }
            cnt++;
        }
    }

public:
    ALGraph(const GraphType t, const int vn, const int an)
        : type(t), vexNum(vn), arcNum(an), vertices(new VNode[vexNum]), visited(new int[vexNum])
    {
        for (int i = 0; i < vexNum; i++)
        {
            vertices[i].data = (VertexType)(i + 1);
        }

        // build the graph
        for (int c = 0; c < arcNum; c++)
        {
            int v1, v2;
            int w = 0;
            cin >> v1 >> v2;
            if (isNetwork())
            {
                cin >> w;
            }
            int i = locateV(v1);
            int j = locateV(v2);
            ArcNode *p = new ArcNode;
            p->nextarc = vertices[i].firstarc;
            vertices[i].firstarc = p;
            p->adjvex = j;
            p->weight = isNetwork() ? w : 1;

            if (isUndirected())
            {
                p = new ArcNode;
                p->nextarc = vertices[j].firstarc;
                vertices[j].firstarc = p;
                p->adjvex = i;
                p->weight = isNetwork() ? w : 1;
            }
        }
    }

    ~ALGraph()
    {
        delete[] vertices;
        delete[] visited;
    }

    void DFSTraverse(int (ALGraph::*MyVisit)(int))
    {
        memset(visited, 0, sizeof(int) * vexNum);
        for (int v = 0; v < vexNum; v++)
        {
            if (!visited[v])
            {
                cout << "{";
                dfs(v, MyVisit);
                cout << "}";
            }
        }
        cout << "\n";
    }

    void BFSTraverse(int (ALGraph::*MyVisit)(int))
    {
        memset(visited, 0, sizeof(int) * vexNum);
        queue<int> q;

        for (int v = 0; v < vexNum; v++)
        {
            if (!visited[v])
            {
                cout << "{";
                visited[v] = 1;
                (this->*MyVisit)(v);
                q.push(v);
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    int cnt = 0;
                    for (auto w = firstAdjVex(u); w; w = nextAdjVex(u, ++cnt))
                    {
                        if (!visited[w->adjvex])
                        {
                            visited[w->adjvex] = 1;
                            cout << " ";
                            (this->*MyVisit)(w->adjvex);
                            q.push(w->adjvex);
                        }
                    }
                }
                cout << "}";
            }
        }
    }

    int out_element(int n)
    {
        if (n >= vexNum)
        {
            return -1;
        }
        cout << vertices[n].data;
        return n;
    }

}; // class ALGraph

int main()
{
    int vexnum, arcnum;
    cin >> vexnum >> arcnum;
    ALGraph mg(UDG, vexnum, arcnum);
    mg.DFSTraverse(&ALGraph::out_element);
    mg.BFSTraverse(&ALGraph::out_element);
    return 0;
}