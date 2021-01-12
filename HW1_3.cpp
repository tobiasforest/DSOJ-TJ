#ifdef __GNUC__
#include <bits/stdc++.h>
#endif
 
#ifdef _MSC_VER
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#endif
 
using namespace std;
 
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR -1
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;
typedef unsigned ElemType;
 
struct SqList
{
    ElemType *elem = nullptr;
    size_t length = 0;
    SqList(size_t len) : length(len)
    {
        elem = new ElemType[len]();
        for (size_t i = 0; i < len; i++)
        {
            cin >> elem[i];
        }
    }
    ~SqList() { delete[] elem; }
    void display()
    {
        for (size_t i = 0; i < length; i++)
        {
            cout << elem[i] << ' ';
        }
        cout << endl;
        return;
    }
};
 
Status ListDeleteByValue_Sq(SqList &L, ElemType &e)
{
    int count = 0;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
        {
            count++;
        }
        else
        {
            L.elem[i - count] = L.elem[i];
        }
    }
    L.length -= count;
    return count;
}
 
int main()
{
    size_t len = 0;
    size_t action_times = 0;
    cin >> len;
    SqList L(len);
    cin >> action_times;
 
    while (action_times--)
    {
        ElemType tmp = 0;
        cin >> tmp;
        cout << ListDeleteByValue_Sq(L, tmp) << endl;
    }
 
    L.display();
    return 0;
}