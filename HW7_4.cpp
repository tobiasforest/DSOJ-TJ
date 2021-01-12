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
#include <stack>
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
    DN,        // Directed Network
    UDG,       // Undirected Graph
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
    int *indegree = nullptr;
    int *ve = nullptr;
    int *vl = nullptr;
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

    int findInDegree()
    {
        for (int i = 0; i < vexNum; i++)
        {
            ArcNode *cur = vertices[i].firstarc;
            while (cur)
            {
                indegree[cur->adjvex]++;
                cur = cur->nextarc;
            }
        }
        return 0;
    }

    int topologicalOrder(stack<int> &t)
    {
        findInDegree();
        stack<int> s;
        for (int i = 0; i < vexNum; i++)
        {
            if (!indegree[i])
            {
                s.push(i);
            }
        }
        int count = 0;
        memset(ve, 0, sizeof(int) * vexNum);

        while (!s.empty())
        {
            int j = s.top();
            s.pop();
            t.push(j);
            count++;
            for (ArcNode *p = vertices[j].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                if (!--indegree[k])
                {
                    s.push(k);
                }
                if (ve[j] + p->weight > ve[k])
                {
                    ve[k] = ve[j] + p->weight;
                }
            }
        }

        return count < vexNum ? 0 : 1;
    }

    int findCriticalPath()
    {
        stack<int> t;
        if (!topologicalOrder(t))
        {
            return 0;
        }
        for (int i = 0; i < vexNum; i++)
        {
            vl[i] = ve[vexNum - 1];
        }

        while (!t.empty())
        {
            int j = t.top();
            t.pop();
            for (ArcNode *p = vertices[j].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                int dut = p->weight;
                if (vl[k] - dut < vl[j])
                {
                    vl[j] = vl[k] - dut;
                }
            }
        }

        return 1;
    }

public:
    ALGraph(const GraphType t, const int vn, const int an)
        : type(t), vexNum(vn), arcNum(an),
          vertices(new VNode[vexNum]), visited(new int[vexNum]),
          indegree(new int[vexNum]), ve(new int[vexNum]),
          vl(new int[vexNum])
    {
        for (int i = 0; i < vexNum; i++)
        {
            vertices[i].data = (VertexType)(i + 1);
        }
        memset(indegree, 0, sizeof(int) * vexNum);

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
        delete[] indegree;
        delete[] ve;
        delete[] vl;
    }

    int getCriticalTime()
    {
        findCriticalPath();
        int t = 0;
        for (int j = 0; j < vexNum; j++)
        {
            for (ArcNode *p = vertices[j].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                int dut = p->weight;
                int ee = ve[j];       // e(j)
                int el = vl[k] - dut; // l(j)
                if (ee == el)
                {
                    t += dut;
                }
            }
        }
        return t;
    }

    int getCriticalPath()
    {
        for (int j = 0; j < vexNum; j++)
        {
            for (ArcNode *p = vertices[j].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                int dut = p->weight;
                int ee = ve[j];       // e(j)
                int el = vl[k] - dut; // l(j)
                if (ee == el)
                {
                    cout << vertices[j].data << "->" << vertices[k].data << "\n";
                }
            }
        }
        return 0;
    }

}; // class ALGraph

int main()
{
    int vexnum, arcnum;
    cin >> vexnum >> arcnum;
    ALGraph mg(DN, vexnum, arcnum);
    cout << mg.getCriticalTime() << "\n";
    mg.getCriticalPath();
    return 0;
}