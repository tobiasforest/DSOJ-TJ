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

int out_element(int n)
{
    cout << n;
    return n;
}

class MGraph
{
protected:
    int **base = nullptr; // pointer to the matrix
    GraphType type = UNDEFINED;
    int vexNum = 0;
    int arcNum = 0;
    int *vexs = nullptr;
    int *visited = nullptr;
    bool isNetwork() const { return type == DN || type == UDN; }
    bool isUndirected() const { return type == UDG || type == UDN; }

    int firstAdjVex(int v)
    {
        for (int i = 0; i < vexNum; i++)
        {
            if (base[v][i])
            {
                return i;
            }
        }
        return -1;
    }

    int nextAdjVex(int v, int w)
    {
        for (int i = w + 1; i < vexNum; i++)
        {
            if (base[v][i])
            {
                return i;
            }
        }
        return -1;
    }

    void dfs(int v, int (*visit)(int))
    {
        visited[v] = 1;
        visit(v);

        for (int w = firstAdjVex(v); w >= 0; w = nextAdjVex(v, w))
        {
            if (!visited[w])
            {
                cout << " ";
                dfs(w, visit);
            }
        }
    }

public:
    MGraph(const GraphType t, const int vn, const int an) : type(t), vexNum(vn), arcNum(an)
    {
        vexs = new int[vexNum + 1]();
        for (int i = 0; i < vexNum; i++)
        {
            vexs[i] = i;
        }
        visited = new int[vexNum];
        base = new int *[vexNum];
        for (int i = 0; i < vexNum; i++)
        {
            base[i] = new int[vexNum];
            memset(base[i], 0, sizeof(int) * vexNum);
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
            int i = locate(v1);
            int j = locate(v2);
            base[i][j] = isNetwork() ? w : 1;
            if (isUndirected())
            {
                base[j][i] = base[i][j];
            }
        }
    }

    ~MGraph()
    {
        for (int i = 0; i < vexNum; i++)
        {
            delete[] base[i];
            base[i] = nullptr;
        }
        delete[] base;
        delete[] vexs;
        delete[] visited;
    }

    int locate(int v)
    {
        for (int i = 0; i < vexNum; i++)
        {
            if (v == vexs[i])
            {
                return i;
            }
        }
        return inf;
    }

    void DFSTraverse(int (*MyVisit)(int))
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

    void BFSTraverse(int (*MyVisit)(int))
    {
        memset(visited, 0, sizeof(int) * vexNum);
        queue<int> q;

        for (int v = 0; v < vexNum; v++)
        {
            if (!visited[v])
            {
                cout << "{";
                visited[v] = 1;
                MyVisit(v);
                q.push(v);
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    for (int w = firstAdjVex(u); w >= 0; w = nextAdjVex(u, w))
                    {
                        if (!visited[w])
                        {
                            visited[w] = 1;
                            cout << " ";
                            MyVisit(w);
                            q.push(w);
                        }
                    }
                }
                cout << "}";
            }
        }
    }

    int displayVexs()
    {
        for (int i = 0; i < vexNum; i++)
        {
            cout << vexs[i] << " ";
        }
        cout << "\n";
        return 0;
    }

    int displayMatrix()
    {
        for (int i = 0; i < vexNum; i++)
        {
            for (int j = 0; j < vexNum; j++)
            {
                cout << setw(4) << base[i][j];
            }
            cout << "\n";
        }
        return 0;
    }

    int displayList()
    {
        for (int i = 0; i < vexNum; i++)
        {
            cout << vexs[i] << "-->";
            for (int j = vexNum - 1; j >= 0; j--)
            {
                if (base[i][j])
                {
                    cout << j;
                    if (isNetwork())
                    {
                        cout << "," << base[i][j];
                    }
                    cout << " ";
                }
            }
            cout << "\n";
        }
        return 0;
    }
}; // class MGraph

int main()
{
    int vexnum, arcnum;
    cin >> vexnum >> arcnum;
    MGraph mg(UDG, vexnum, arcnum);
    mg.DFSTraverse(out_element);
    mg.BFSTraverse(out_element);

    return 0;
}