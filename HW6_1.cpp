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

enum class PointerTag
{
    LINK,
    THREAD
};
ostream &operator<<(ostream &out, enum PointerTag t) { return out << (int)t; }
struct ThreadNode
{
    char value;
    ThreadNode *left_child = nullptr;
    ThreadNode *right_child = nullptr;
    PointerTag left_tag = PointerTag::LINK;
    PointerTag right_tag = PointerTag::LINK;
    ThreadNode(const char v = -1) : value(v) {}
    bool isLeaf() const { return !left_child && !right_child; }
}; // struct ThreadNode
ostream &operator<<(ostream &out, struct ThreadNode tn) { return out << tn.value << tn.left_tag << tn.right_tag; }

class ThreadBinaryTree
{
protected:
    ThreadNode *root = nullptr;
    ThreadNode *head_pre = nullptr;
    char seq[1024] = {'\0'};
    ThreadNode *create_tree_pre(char *&ptr)
    {
        ThreadNode *pNewNode = nullptr;
        if (ptr && *ptr && *ptr != '#')
        {
            pNewNode = new ThreadNode(*ptr);
            pNewNode->left_child = create_tree_pre(++ptr);
            pNewNode->right_child = create_tree_pre(++ptr);
        }
        return pNewNode;
    }
    void pre_thread(ThreadNode *&cur, ThreadNode *&prev)
    {
        if (cur)
        {
            if (!cur->left_child)
            {
                cur->left_tag = PointerTag::THREAD;
                cur->left_child = prev;
            }
            if (prev && !prev->right_child)
            {
                prev->right_tag = PointerTag::THREAD;
                prev->right_child = cur;
            }
            prev = cur;
            if (cur->left_tag == PointerTag::LINK)
            {
                pre_thread(cur->left_child, prev);
            }
            if (cur->right_tag == PointerTag::LINK)
            {
                pre_thread(cur->right_child, prev);
            }
        }
    }

    char traverse_in(ThreadNode *p_node) const
    {
        if (p_node)
        {
            if (p_node->left_tag == PointerTag::LINK)
            {
                traverse_in(p_node->left_child);
            }
            cout << p_node->value;
            if (p_node->right_tag == PointerTag::LINK)
            {
                traverse_in(p_node->right_child);
            }
            return p_node->value;
        }
        return 0;
    }
    char traverse_post(ThreadNode *p_node) const
    {
        if (p_node)
        {
            if (p_node->left_tag == PointerTag::LINK)
            {
                traverse_in(p_node->left_child);
            }
            if (p_node->right_tag == PointerTag::LINK)
            {
                traverse_in(p_node->right_child);
            }
            cout << p_node->value;
            return p_node->value;
        }
        return 0;
    }
    void print_tree(ThreadNode *p_node, const int depth) const
    {
        if (p_node)
        {
            if (p_node->right_tag == PointerTag::LINK)
            {
                print_tree(p_node->right_child, depth + 1);
            }
            for (int i = 0; i < depth; i++)
            {
                cout << "     ";
            }
            cout << *p_node << endl;
            if (p_node->left_tag == PointerTag::LINK)
            {
                print_tree(p_node->left_child, depth + 1);
            }
        }
    }
    void delete_node(ThreadNode *&p)
    {
        if (p)
        {
            if (p->left_tag == PointerTag::LINK && p->left_child)
            {
                delete_node(p->left_child);
            }
            if (p->right_tag == PointerTag::LINK && p->right_child)
            {
                delete_node(p->right_child);
            }
            delete p;
            p = nullptr;
        }
    }

public:
    ThreadBinaryTree() : head_pre(new ThreadNode())
    { // pre-order
        char *p = seq;
        cin >> seq;
        root = create_tree_pre(p);

        head_pre->left_tag = PointerTag::LINK;
        head_pre->right_tag = PointerTag::THREAD;
        head_pre->right_child = head_pre;

        ThreadNode *pre = nullptr;
        if (!root)
        {
            head_pre->left_child = head_pre;
        }
        else
        {
            head_pre->left_child = root;
            pre = head_pre;
            pre_thread(root, pre);
            pre->right_tag = PointerTag::THREAD;
            pre->right_child = head_pre;
            head_pre->right_child = pre;
        }
    }
    ~ThreadBinaryTree() { delete_node(root); }
    ThreadNode *get_root() const { return root; }
    void traverse_pre() const
    {
        ThreadNode *cur = nullptr;
        if (head_pre)
        {
            cur = head_pre->left_child;
            while (cur != head_pre)
            {
                while (cur && cur->left_tag == PointerTag::LINK)
                {
                    std::cout << cur->value;
                    cur = cur->left_child;
                }
                std::cout << cur->value;
                cur = cur->right_child;
            }
        }
        std::cout << endl;
    }
    void traverse_post() const
    {
        traverse_post(root);
        cout << endl;
    }
    void traverse_level() const
    {
        queue<ThreadNode *> q;
        if (root)
        {
            q.push(root);
            while (!q.empty())
            {
                ThreadNode *p_node = q.front();
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
}; // class ThreadBinaryTree

int main()
{
    ThreadBinaryTree tree;
    tree.display();
    tree.traverse_pre();

    return 0;
}