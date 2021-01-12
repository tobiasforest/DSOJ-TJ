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
#define MAX_N 2000

using namespace std;

enum GraphType
{
    UNDEFINED, // Undefined
    DG,        // Directed Graph
    DN,        // Directed Network
    UDG,       // Undirected Graph
    UDN        // Undirected Network
};

class MGraph
{

protected:
    int **base = nullptr; // pointer to the matrix
    GraphType type = UNDEFINED;
    int vexNum = 0;
    int arcNum = 0;
    int *vexs = nullptr;
    int *path = nullptr;
    inline bool isNetwork() const { return type == DN || type == UDN; }
    inline bool isUndirected() const { return type == UDG || type == UDN; }

    int locate(const int v) const
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

    int printPath(const int *path, const int edgeCount) const
    {
        for (int i = 0; i <= edgeCount; i++)
        {
            if (i)
            {
                cout << "->";
            }
            cout << vexs[path[i]];
        }
        cout << "\n";
        return 1;
    }

public:
    MGraph(const GraphType t, const int vn, const int an)
        : type(t), vexNum(vn), arcNum(an),
          vexs(new int[vexNum]), path(new int[MAX_N])
    {
        for (int i = 0; i < vexNum; i++)
        {
            vexs[i] = i + 1;
        }

        base = new int *[vexNum];
        for (int i = 0; i < vexNum; i++)
        {
            base[i] = new int[vexNum];
            memset(base[i], 0, sizeof(int) * vexNum);
        }

        cout << "Please input src and dst (and weight, "
                "if needed) of each arc: \n";

        // build the graph
        for (int c = 0; c < arcNum; c++)
        {
            int src_v, dst_v;
            int w = 0;
            cin >> src_v >> dst_v;
            if (isNetwork())
            {
                cin >> w;
            }
            int i_src_v = locate(src_v);
            int j_dst_v = locate(dst_v);
            base[i_src_v][j_dst_v] = isNetwork() ? w : 1;
            if (isUndirected())
            {
                base[j_dst_v][i_src_v] = base[i_src_v][j_dst_v];
            }
        }

        memset(path, 0, sizeof(int) * MAX_N);
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
        delete[] path;
    }

    int DFS_OnePath(
        const int currentArc = 0,
        const int edgeCount = 0,
        int ansNum = 0)
    {
        path[edgeCount] = currentArc;

        if (edgeCount == arcNum)
        {
            cout << "Path No." << ++ansNum << ": ";
            printPath(path, edgeCount);
        }

        for (int i = 0; i < vexNum; i++)
        {
            if (base[currentArc][i])
            {
                int temp = base[currentArc][i];
                base[currentArc][i] = 0;
                if (isUndirected())
                {
                    base[i][currentArc] = 0;
                }

                ansNum = DFS_OnePath(i, edgeCount + 1, ansNum);
                base[currentArc][i] = temp;
                if (isUndirected())
                {
                    base[i][currentArc] = temp;
                }
            }
        }
        return ansNum;
    }

}; // class MGraph

int main()
{
    (void)freopen(".\\HW7_6_input.txt", "rb", stdin);
    int vexnum, arcnum, count = 0;
    cout << "Please input the numbers of "
            "vertices and arcs respectively: \n";
    cin >> vexnum >> arcnum;
    MGraph mg(UDG, vexnum, arcnum);

    cout << "Found accessible paths are: \n";
    if (!(count = mg.DFS_OnePath()))
    {
        cout << "Not found!\n";
    }
    else
    {
        cout << "Done! There are "
             << count << " paths found! \n";
    }
    fclose(stdin);

    return 0;
}