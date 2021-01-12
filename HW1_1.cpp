#ifdef __GNUC__
#include <bits/stdc++.h>
#endif
 
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cmath>
#endif
 
using namespace std;
 
struct Student
{
    char name[20] = {'\0'}; // student name
    char no[20] = {'\0'};   // student number
    Student &operator=(Student &s)
    {
        strcpy(name, s.name);
        strcpy(no, s.no);
        return *this;
    }
};
 
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR -1
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;
typedef Student ElemType;
 
typedef struct LNode
{
    ElemType data;
    LNode *next = nullptr;
} LNode, *LinkList;
 
Status ListInsert_L(LinkList &L, int i, ElemType &e)
{
    LinkList p = L, s;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1)
        return ERROR;
    s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
 
Status ListDelete_L(LinkList &L, int i)
{
    LinkList p = L, q;
    int j = 0;
    while (p->next && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    delete q;
    return OK;
}
 
Status ListCheckByName_L(LinkList &L, char name[])
{
    int i;
    LinkList p;
 
    p = L->next;
    i = 1;
    while (p && strcmp(p->data.name, name))
    {
        p = p->next;
        i++;
    }
    if (!p)
    {
        cout << INFEASIBLE << endl;
        return ERROR;
    }
    else
    {
        cout << i << " " << p->data.no << " " << p->data.name << endl;
        return OK;
    }
}
 
Status ListCheckByNo_L(LinkList &L, char no[])
{
    int i;
    LinkList p;
 
    p = L->next;
    i = 1;
    while (p && strcmp(p->data.no, no))
    {
        p = p->next;
        i++;
    }
    if (!p)
    {
        cout << INFEASIBLE << endl;
        return ERROR;
    }
    else
    {
        cout << i << " " << p->data.no << " " << p->data.name << endl;
        return OK;
    }
}
 
Status ListDestroy_L(LinkList &L)
{
    LinkList q;
    while (L)
    {
        q = L->next;
        delete L;
        L = q;
    }
    return OK;
}
 
int ListLength_L(LinkList &L)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}
 
int main()
{
    int student_num = 0;
    cin >> student_num;
    LinkList student_list = new LNode;
    LNode *pList = student_list;
 
    for (int i = 0; i < student_num; i++)
    {
        pList->next = new LNode;
        pList = pList->next;
        cin >> pList->data.no >> pList->data.name;
    }
 
    while (!cin.eof())
    {
        char order[20] = {'\0'};
        cin >> order;
        if (!strcmp("end", order))
        {
            cout << ListLength_L(student_list) << endl;
            break;
        }
        else if (!strcmp("insert", order))
        {
            Student s;
            int pos;
            cin >> pos >> s.no >> s.name;
            cout << ListInsert_L(student_list, pos, s) << endl;
        }
        else if (!strcmp("remove", order))
        {
            int pos;
            cin >> pos;
            cout << ListDelete_L(student_list, pos) << endl;
        }
        else if (!strcmp("check", order))
        {
            cin >> order;
            if (!strcmp("name", order))
            {
                char name[20] = {'\0'};
                cin >> name;
                ListCheckByName_L(student_list, name);
            }
            else if (!strcmp("no", order))
            {
                char no[20] = {'\0'};
                cin >> no;
                ListCheckByNo_L(student_list, no);
            }
        }
    }
 
    ListDestroy_L(student_list);
    return 0;
}