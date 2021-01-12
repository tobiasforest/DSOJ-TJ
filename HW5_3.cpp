#ifdef __GNUC__
#include <bits/stdc++.h>
#endif // __GNUC__
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <queue>
#endif // _MSC_VER

using namespace std;

struct Node
{
    char value;
    Node *left_child = nullptr;
    Node *right_child = nullptr;
    Node(const char v) : value(v) {}
    bool is_leaf() const { return !left_child && !right_child; }
}; // struct Node

class MyBinaryTree
{
protected:
    Node *root = nullptr;
    Node *create_tree_pre(char *&ptr)
    {
        Node *pNewNode = nullptr;
        if (ptr && *ptr && *ptr != '#')
        {
            pNewNode = new Node(*ptr);
            pNewNode->left_child = create_tree_pre(++ptr);
            pNewNode->right_child = create_tree_pre(++ptr);
        }
        return pNewNode;
    }
    char traverse_pre(Node *p_node) const
    {
        if (p_node)
        {
            cout << p_node->value;
            traverse_pre(p_node->left_child);
            traverse_pre(p_node->right_child);
            return p_node->value;
        }
        return 0;
    }
    char traverse_in(Node *p_node) const
    {
        if (p_node)
        {
            traverse_in(p_node->left_child);
            cout << p_node->value;
            traverse_in(p_node->right_child);
            return p_node->value;
        }
        return 0;
    }
    char traverse_post(Node *p_node) const
    {
        if (p_node)
        {
            traverse_post(p_node->left_child);
            traverse_post(p_node->right_child);
            cout << p_node->value;
            return p_node->value;
        }
        return 0;
    }
    void print_tree(Node *p_node, const int depth) const
    {
        if (p_node)
        {
            print_tree(p_node->right_child, depth + 1);
            for (int i = 0; i < depth; i++)
            {
                cout << "     ";
            }
            cout << p_node->value << endl;
            print_tree(p_node->left_child, depth + 1);
        }
    }
    void delete_node(Node *p)
    {
        if (p)
        {
            delete_node(p->left_child);
            delete_node(p->right_child);
            delete p;
        }
    }

public:
    MyBinaryTree()
    { // pre-order
        char seq[1024] = {'\0'}, *p = seq;
        int n = 0;
        cin >> n;
        n <<= 1;
        while (n--)
        {
            string order;
            cin >> order;
            if (order == "push")
            {
                cin >> *p++;
            }
            else if (order == "pop")
            {
                *p++ = '#';
            }
        }
        root = create_tree_pre(p = seq);
    }
    ~MyBinaryTree()
    {
        delete_node(root);
    }
    Node *get_root() const { return root; }
    void traverse_pre() const
    {
        traverse_pre(root);
        cout << endl;
    }
    void traverse_in() const
    {
        traverse_in(root);
        cout << endl;
    }
    void traverse_post() const
    {
        traverse_post(root);
        cout << endl;
    }
    void traverse_level() const
    {
        queue<Node *> q;
        if (root)
        {
            q.push(root);
            while (!q.empty())
            {
                Node *p_node = q.front();
                cout << p_node->value;
                q.pop();
                if (p_node->left_child)
                {
                    q.push(p_node->left_child);
                }
                if (p_node->right_child)
                {
                    q.push(p_node->right_child);
                }
            }
        }
        cout << endl;
    }
    void display() const { print_tree(root, 0); }
}; // class MyBinaryTree

int main()
{
    MyBinaryTree tree;
    tree.traverse_post();

    return 0;
}