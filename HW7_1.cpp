#ifdef __GNUC__
#include <bits/stdc++.h>
#endif // __GNUC__
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <ctime>
#include <iomanip>
#include <queue>
#endif // _MSC_VER

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

class MGraph
{
protected:
    int **base = nullptr; // pointer to the matrix
    GraphType type = UNDEFINED;
    int vexNum = 0;
    int arcNum = 0;
    char *vexs = nullptr;
    bool isNetwork() const { return type == DN || type == UDN; }
    bool isUndirected() const { return type == UDG || type == UDN; }

public:
    MGraph(const GraphType t, const int vn, const int an) : type(t), vexNum(vn), arcNum(an)
    {
        vexs = new char[vexNum + 1]();
        base = new int *[vexNum];
        for (int i = 0; i < vexNum; i++)
        {
            base[i] = new int[arcNum]();
        }
        cin >> vexs;

        // build the graph
        for (int c = 0; c < arcNum; c++)
        {
            char v1, v2;
            int w;
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
    }

    int locate(char v)
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
    GraphType type;
    int vexnum, arcnum;
    cin >> type >> vexnum >> arcnum;
    MGraph mg(type, vexnum, arcnum);
    mg.displayVexs();
    mg.displayMatrix();
    mg.displayList();

    return 0;
}