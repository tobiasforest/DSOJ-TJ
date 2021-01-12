#ifdef __GNUC__
#include <bits/stdc++.h>
#endif
 
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#endif
 
using namespace std;
 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;
typedef int ElemType;
 
typedef struct Node
{
    ElemType data = 0;
    struct Node *next = nullptr;
} * pNode;
 
struct LinkList
{
    pNode head = nullptr;
    LinkList(const size_t n) : head(new Node)
    { // create a linked list through head-inserted method
        pNode p = nullptr;
        for (size_t i = n; i > 0; i--)
        {
            p = new Node;
            cin >> p->data;
            p->next = head->next;
            head->next = p;
        }
    }
    LinkList(const size_t n, int) : head(new Node)
    { // create a linked list through tail-inserted method
        pNode p = head;
        for (size_t i = 0; i < n; i++)
        {
            p->next = new Node;
            p = p->next;
            cin >> p->data;
        }
    }
    ~LinkList()
    { // destroy the linked list
        pNode q = nullptr;
        while (head)
        {
            q = head->next;
            delete head;
            head = q;
        }
    }
    Status insert(const size_t n, const ElemType &e)
    { // insert a Node whose value is e, before n_th position
        pNode p = head, q = nullptr;
        size_t i = 0;
        for (; i < n - 1 && p; i++)
        {
            p = p->next;
        }
        if (i > n - 1 || !p)
        {
            return ERROR;
        }
        q = new Node;
        q->data = e;
        q->next = p->next;
        p->next = q;
        return OK;
    }
    Status _delete(const size_t n)
    { // delete n_th Node
        pNode p = head, q = nullptr;
        size_t i = 0;
        for (; i < n - 1 && p; i++)
        {
            p = p->next;
        }
        if (i > n - 1 || !p)
        {
            return ERROR;
        }
        q = p->next;
        p->next = q->next;
        delete q;
        return OK;
    }
    Status searchByValue(const ElemType &e)
    {
        pNode p = head->next;
        for (int i = 1; p; i++)
        {
            if (p->data == e)
            {
                return i;
            }
            p = p->next;
        }
        return INFEASIBLE;
    }
    size_t count()
    {
        size_t n = 0;
        pNode p = head->next;
        while (p)
        {
            n++;
            p = p->next;
        }
        return n;
    }
    void display()
    {
        pNode p = head->next;
        while (p)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    Status distinguishing()
    {
        pNode p = head->next, q, k, tmp = nullptr;
        while (p->next)
        {
            q = p;
            k = q->next;
            while (k)
            {
                if (p->data == k->data)
                {
                    q->next = k->next;
                    delete k;
                    k = q->next;
                }
                else
                {
                    q = k;
                    k = k->next;
                }
            }
            if (p->next)
            {
                p = p->next;
            }
        }
        return OK;
    }
    Status reverse(const size_t O, const size_t D)
    {
        if (O < 1U || O >= D)
        {
            return ERROR;
        }
        size_t len = 0;
        pNode cur = head->next, o = nullptr, o_pre = nullptr, d_next = nullptr;
 
        while (cur)
        {
            ++len;
            if (len == O - 1)
            {
                o_pre = cur;
            }
            if (len == D + 1)
            {
                d_next = cur;
            }
            cur = cur->next;
        }
        if (len < D)
        {
            return ERROR;
        }
        o = o_pre ? o_pre->next : head->next;
 
        pNode tmp_pre = d_next, tmp = nullptr;
 
        while (o != d_next)
        {
            tmp = o->next;
            o->next = tmp_pre;
            tmp_pre = o;
            o = tmp;
        }
 
        if (o_pre)
        {
            o_pre->next = tmp_pre;
        }
        else
        {
            head->next = tmp_pre;
        }
        return OK;
    }
};
 
int main()
{
    size_t n = 0;
    ios::sync_with_stdio(false);
    cin >> n;
    LinkList l(n, 0);
    cin >> n;
    while (n--)
    {
        size_t left, right;
        cin >> left >> right;
        if (l.reverse(left, right))
        {
            l.display();
        }
        else
        {
            cout << 0 << endl;
        }
    }
 
    return 0;
}