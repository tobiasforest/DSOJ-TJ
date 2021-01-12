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

#include <windows.h>
#include <conio.h>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;
typedef struct term
{
    double coef = 0.0; // coefficient
    int expn = 0;      // exponent
    term() { cin >> coef >> expn; }
    term(const double c, const int e) : coef(c), expn(e) {}
} ElemType;

typedef struct Node : public ElemType
{
    struct Node *next = nullptr;
    Node() : term() {}
    Node(const double c, const int e) : term(c, e) {}
    Node(const Node &n) : term(n.coef, n.expn) {}
    bool operator==(const Node &n) const { return expn == n.expn; }
    bool operator<(const Node &n) const { return expn < n.expn; }
    bool operator>(const Node &n) const { return expn > n.expn; }
    bool operator==(const double d) const { return coef == d; }
} * pNode;

typedef struct polynominal
{
    pNode head;
    polynominal(const size_t n) : head(new Node(0.0, 0))
    {
        for (size_t i = 0; i < n; i++)
        {
            pNode t = new Node();
            insert(t);
        }
    }
    polynominal() : head(new Node(0.0, 0)) {}
    polynominal(const polynominal &p) : head(p.head) {}
    polynominal(const polynominal *pp) : head(pp ? pp->head : nullptr) {}
    polynominal &clear()
    { // clear all elements and recover to an empty linked list
        while (head)
        {
            pNode p = head->next;
            delete head;
            head = p;
        }
        return *this;
    }
    ~polynominal() {}
    polynominal &insert(pNode p_new)
    { // insert an element into the linked list on the existed rule
        pNode m = head, n = head->next;

        do
        {
            if (!p_new)
            {
                break;
            }
            if (!(p_new->coef))
            {
                delete p_new;
                break;
            }
            if (!head->next)
            {
                head->next = p_new;
            }
            else
            {
                while (true)
                {
                    if (!n->next && *n < *p_new)
                    {
                        n->next = p_new;
                        break;
                    }
                    else if (*n > *p_new)
                    {
                        m->next = p_new;
                        p_new->next = n;
                        break;
                    }
                    else if (*n == *p_new)
                    {
                        n->coef += p_new->coef;
                        delete p_new;
                        break;
                    }
                    else
                    {
                        m = n;
                        n = n->next;
                    }
                }
            }
        } while (false);
        return *this;
    }
    polynominal operator+(const polynominal &p)
    {
        polynominal result;
        pNode pLeft = this->head->next, pRight = p.head->next, pp = nullptr;
        while (pLeft && pRight)
        {
            if (*pLeft == *pRight)
            {
                pp = new Node(pLeft->coef + pRight->coef, pLeft->expn);
                pLeft = pLeft->next;
                pRight = pRight->next;
            }
            else if (*pLeft < *pRight)
            {
                pp = new Node(*pLeft);
                pLeft = pLeft->next;
            }
            else // if (*pLeft > *pRight)
            {
                pp = new Node(*pRight);
                pRight = pRight->next;
            }
            result.insert(pp);
        }
        while (pLeft)
        {
            pp = new Node(*pLeft);
            result.insert(pp);
            pLeft = pLeft->next;
        }
        while (pRight)
        {
            pp = new Node(*pRight);
            result.insert(pRight);
            pRight = pRight->next;
        }

        return result;
    }
    polynominal operator*(const polynominal &p)
    {
        polynominal result;
        pNode pLeft = this->head->next, pRight = p.head->next;

        while (pLeft)
        {
            pRight = p.head->next;
            while (pRight)
            {
                pNode p = new Node(pLeft->coef * pRight->coef, pLeft->expn + pRight->expn);
                result.insert(p);
                pRight = pRight->next;
            }
            pLeft = pLeft->next;
        }
        return result;
    }
} LinkList;
ostream &operator<<(ostream &out, const polynominal &poly)
{
    pNode p = poly.head->next;
    while (p)
    {
        out << showpos << p->coef << "x^";
        out << noshowpos << p->expn;
        p = p->next;
    }
    return out;
}

inline void menu()
{
    system("cls");
    cout << "*****************************" << endl
         << "*   Polynomial Calculator   *" << endl
         << "*****************************" << endl
         << endl;
}

int main()
{
    size_t m, n;
    int choice;
    menu();
    cout << "Welcome! This program is committed to conducting calculations of two polynominals. " << endl;

    cout << "Please input the number of terms of the first polynominal: " << endl;
    cin >> m;
    cout << "Please input coefficient and exponent of each term relatively: " << endl;
    LinkList l_m(m);

    cout << "Please input the number of terms of the second polynominal: " << endl;
    cin >> n;
    cout << "Please input coefficient and exponent of each term relatively: " << endl;
    LinkList l_n(n);
    LinkList add(nullptr), mul(nullptr);

    bool pass = false;
    while (!pass)
    {
        menu();
        cout << "Input successfully! " << endl;
        cout << "The first polynominal is: " << endl
             << l_m << endl;
        cout << "The second polynominal is: " << endl
             << l_n << endl;

        cout << endl
             << "Command list: " << endl
             << "    0> add" << endl
             << "    1> multiple" << endl
             << "    2> add and multiple" << endl
             << endl
             << "Please input your choice: ";

        switch (choice = _getche() - '0')
        {
        case 0:
            add = l_m + l_n;
            cout << endl
                 << "The result of two polynominals added is: " << endl;
            cout << add << endl;
            pass = true;
            break;
        case 1:
            mul = l_m * l_n;
            cout << endl
                 << "The result of two polynominals multiplied is: " << endl;
            cout << mul << endl;
            pass = true;
            break;
        case 2:
            add = l_m + l_n;
            cout << endl
                 << "The result of two polynominals added is: " << endl;
            cout << add << endl;
            mul = l_m * l_n;
            cout << endl
                 << "The result of two polynominals multiplied is: " << endl;
            cout << mul << endl;
            pass = true;
            break;
        default:
            cerr << endl
                 << "Input illegal. Please try again. " << endl;
            Sleep(1000);
        }
    }
    add.clear();
    mul.clear();

    (void)_getch();
    return 0;
}