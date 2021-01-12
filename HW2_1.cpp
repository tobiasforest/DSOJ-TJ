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
        for (; i < n - 1 && p; i++, p = p->next)
            ;
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
        for (; i < n - 1 && p; i++, p = p->next)
            ;
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
        for (size_t i = 0; p; i++)
        {
            if (p->data == e)
            {
                return Status(i + 1);
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
};

int main()
{
    size_t n = 0, position = 0;
    ElemType value;
    cin >> n;
    LinkList l(n);
    // 0 create

    l.display();
    // 1 display

    cin >> position >> value;
    if (l.insert(position, value))
    {
        l.display();
    }
    else
    {
        cout << -1 << endl;
    }
    // 2 insert

    cin >> position;
    if (l._delete(position))
    {
        l.display();
    }
    else
    {
        cout << -1 << endl;
    }
    // 3 delete

    cin >> value;
    cout << l.searchByValue(value) << endl;
    // 4 search

    cout << l.count() << endl;
    // 5 count

    return 0;
}