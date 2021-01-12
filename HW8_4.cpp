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
#endif

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define LOVERFLOW -1

typedef int Status;
typedef int KeyType;
typedef int ValueType;
typedef struct Element TElemType;

using namespace std;

enum Command
{
    INSERT = 1, // insert a node
    DELETE,     // delete a node
    COUNT,      // count the frequency of a node
    MINIMUM,    // find the smallest node
    PRECURSOR   // find the precursor node of a node
};

struct Element
{
    KeyType key;
    int freq;
    Element(const KeyType &k, const int f = 1)
        : key(k), freq(f) {}
    struct Element &operator=(const struct Element &e)
    {
        key = e.key;
        freq = e.freq;
        return *this;
    }
};

struct Node
{
    TElemType data;
    Node *left_child = nullptr;
    Node *right_child = nullptr;
    Node *father = nullptr;
    Node(const TElemType &e) : data(e) {}
}; // struct Node

class BSTree
{
private:
    Node *root = nullptr;

    Status delete_all(Node *&p)
    {
        if (p)
        {
            delete_all(p->left_child);
            delete_all(p->right_child);
            delete p;
            p = nullptr;
        }
        return OK;
    }

    Status search(Node *T, const KeyType &key, Node *parent, Node *&p)
    {
        if (!T)
        {
            p = parent;
            return FALSE;
        }
        if (key == T->data.key)
        {
            p = T;
            return TRUE;
        }
        else if (key < T->data.key)
        {
            return search(T->left_child, key, T, p);
        }
        else // if (key > T->data.key)
        {
            return search(T->right_child, key, T, p);
        }
    }

    Status insert(Node *&T, const TElemType &e)
    {
        Node *p = nullptr;
        if (!search(T, e.key, nullptr, p))
        {
            Node *s = new Node(e);
            s->father = p;
            if (!p)
            {
                T = s; // new Node becomes root node
            }
            else if (e.key < p->data.key)
            {
                p->left_child = s; // new Node becomes left child of p (p has no left child)
            }
            else // if (e.key > p->data.key)
            {
                p->right_child = s; // new Node becomes right child of p (p has no right child)
            }
            return TRUE;
        }
        else
        {
            p->data.freq++;
            return TRUE;
        }
    }

    Status _delete(Node *&T, const KeyType &key)
    {
        if (!T)
        {
            cout << "None" << endl;
            return FALSE;
        }
        else
        {
            if (key == T->data.key)
            {
                return delete_elem(T);
            }
            else if (key < T->data.key)
            {
                return _delete(T->left_child, key);
            }
            else // if (key > T->data.key)
            {
                return _delete(T->right_child, key);
            }
        }
    }

    Status delete_elem(Node *&p)
    {
        Node *q = nullptr, *s = nullptr;
        if (p->data.freq > 1)
        {
            p->data.freq--;
        }
        else
        {
            if (!p->right_child) // right is null (whereas left may be null)
            {
                q = p;
                p = p->left_child;
                if (p) // judge if p is null
                {
                    p->father = q->father;
                }
                delete q;
                q = nullptr;
            }
            else if (!p->left_child) // left is null (right cannot be null)
            {
                q = p;
                p = p->right_child;
                p->father = q->father; // p cannot be null, no need to judge
                delete q;
                q = nullptr;
            }
            else // neither right nor left is null
            {
                s = p->left_child;
                while (s->right_child)
                { // s is the direct precursors of the in-order traversal，q is parent of s
                    s = s->right_child;
                }
                p->data = s->data; // s replaces p, former children of p become children of s

                q = s->father;
                if (q != p)
                {
                    // original left sub-tree of s => right sub-tree of original father of s
                    //         right sub-tree of p => right sub-tree of s
                    q->right_child = s->left_child;
                }
                else // if (q == p) // s was the left child of original p
                {
                    q->left_child = s->left_child;
                }

                if (s->left_child)
                {
                    s->left_child->father = q;
                }
                delete s;
            }
        }
        return TRUE;
    }

    KeyType mininum()
    {
        Node *p = root;
        if (!p)
        {
            return LOVERFLOW;
        }
        while (p->left_child)
        {
            p = p->left_child;
        }
        return p->data.key;
    }

    Status find_pre(Node *cur)
    {
        if (!cur)
        {
            return LOVERFLOW;
        }
        Node *ret = nullptr;
        if (cur->left_child) // cur has a left child
        {
            ret = cur->left_child;
            while (ret->right_child)
            {
                ret = ret->right_child;
            }
        }
        else // cur has no left child
        {
            // 2 possibilities:
            //   1) cur is a right child, whose precursor is the father
            //   2) cur is a left child, then we should search for its "lowest"
            // father, while the father has a right child
            ret = cur->father;
            while (ret && cur == ret->left_child)
            {
                cur = ret;
                ret = ret->father;
            }
        }
        if (ret)
        {
            cout << ret->data.key << endl;
        }
        else
        {
            cout << "None" << endl;
        }
        return OK;
    }

public:
    BSTree() {}
    ~BSTree() { delete_all(root); }

    Status Search(const KeyType &key, Node *&pre)
    {
        Node *p = root;
        return search(p, key, nullptr, pre);
    }

    Status Delete(const KeyType &key)
    {
        return _delete(root, key);
    }

    Status Count(const KeyType &key)
    {
        Node *p = nullptr;
        Search(key, p);
        cout << (p && key == p->data.key ? p->data.freq : 0) << endl;
        return OK;
    }

    Status Minimum()
    {
        cout << mininum() << endl;
        return OK;
    }

    Status Insert(const KeyType &key)
    {
        // TElemType t(key);
        return insert(root, key);
    }

    Status Precursor(const KeyType &key)
    {
        Node *ret = nullptr, *cur = root;
        // Search(key, cur);

        if (!cur)
        {
            cout << "None" << endl;
            return ERROR;
        }
        while (cur)
        {
            if (key == cur->data.key)
            {
                find_pre(cur);
                return OK;
            }
            if (key < cur->data.key)
            {
                ret = cur;
                cur = cur->left_child;
            }
            else
            {
                ret = cur;
                cur = cur->right_child;
            }
        }

        if (ret)
        {
            if (key < ret->data.key)
            {
                find_pre(ret);
            }
            else
            {
                cout << ret->data.key << endl;
            }
        }
        else
        {
            cout << "None" << endl;
        }

        return OK;
    }

}; // class BSTree

int main()
{
    freopen("HW8_4_input.txt", "rb", stdin);
    int n = 0;
    cin >> n;

    BSTree tree;

    while (n--)
    {
        int op, key;
        cin >> op;
        switch (op)
        {
        case INSERT:
            cin >> key;
            tree.Insert(key);
            break;

        case DELETE:
            cin >> key;
            tree.Delete(key);
            break;

        case COUNT:
            cin >> key;
            tree.Count(key);
            break;

        case MINIMUM:
            tree.Minimum();
            break;

        case PRECURSOR:
            cin >> key;
            tree.Precursor(key);
            break;
        }
    }

    return 0;
}