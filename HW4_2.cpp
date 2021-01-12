#ifdef __GNUC__
#include <bits/stdc++.h>
#endif // __GNUC__

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#endif // _MSC_VER

using namespace std;

class Matrix
{
protected:
    static const int maxn = 100;
    const int X[4] = {0, 0, 1, -1};
    const int Y[4] = {1, -1, 0, 0};
    struct position
    {
        int x = 0;
        int y = 0;
        position &modify(const int _x, const int _y)
        {
            x = _x;
            y = _y;
            return *this;
        }
    } Node; // struct position
    queue<position> q;
    int width;
    int height;
    int base[maxn][maxn] = {0};
    int inq[maxn][maxn] = {0};
    int count = 0; // count of interconnected domains

public:
    Matrix(const int _x, const int _y) : width(_x), height(_y)
    {
        for (int i = 0; i < _x; i++)
        {
            for (int j = 0; j < _y; j++)
            {
                cin >> base[i][j];
            }
        }
    }
    inline int judge(const int x, const int y)
    {
        if (x >= width || x < 0 || y >= height || y < 0)
        { // if overflow return 0
            return 0;
        }
        if (!base[x][y] || inq[x][y])
        { // if the value of the position is 0, or this position has been in the queue
            return 0;
        }
        return 1;
    }
    void bfs(const int x, const int y)
    { // breadth first search
        q.push(Node.modify(x, y));
        inq[x][y] = 1;

        while (!q.empty())
        {
            position top = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int newX = top.x + X[i];
                int newY = top.y + Y[i];

                if (judge(newX, newY))
                { // if the new position is accessible
                    q.push(Node.modify(newX, newY));
                    inq[newX][newY] = 1;
                }
            }
        }
    }
    int calculate()
    {
        for (int i = 1; i < width - 1; i++)
        {
            for (int j = 1; j < height - 1; j++)
            {
                if (base[i][j] && !inq[i][j])
                {
                    count++;
                    bfs(i, j);
                }
            }
        }
        return count;
    }
}; // class Matrix

int main()
{
    int n, m;
    cin >> n >> m;
    Matrix mat(n, m);
    cout << mat.calculate() << endl;
    return 0;
}