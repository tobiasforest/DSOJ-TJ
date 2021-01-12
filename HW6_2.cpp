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
ostream &operator<<(ostream &out, PointerTag t) { return out << (int)t; }
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
    ThreadNode *in_pre = nullptr;
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
    void in_thread(ThreadNode *&cur, ThreadNode *&prev)
    {
        if (cur)
        {
            in_thread(cur->left_child, prev);
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
            in_thread(cur->right_child, prev);
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
    char traverse_in() const
    {
        ThreadNode *p = root;
        while (p)
        {
            while (p->left_tag == PointerTag::LINK)
            {
                p = p->left_child;
            }
            cout << p->value;
            while (p->right_tag == PointerTag::THREAD && p->right_child)
            {
                p = p->right_child;
                cout << p->value;
            }
            p = p->right_child;
        }
        std::cout << "\n";
        return 0;
    }

public:
    ThreadBinaryTree()
    { // in-order
        char *p = seq;
        cin >> seq;
        root = create_tree_pre(p);
        ThreadNode *pre = nullptr;
        in_thread(root, pre);
        pre->right_tag = PointerTag::THREAD;
    }
    ~ThreadBinaryTree() { delete_node(root); }
    ThreadNode *get_root() const { return root; }
    
    int find() const
    {
        char ch = 0, pre = 0, succ = 0;
        int found = 0, succ_rtag, pre_ltag;
        std::cin >> ch;

        ThreadNode *p = root;
        while (p && !found)
        {
            while (p->left_tag == PointerTag::LINK)
            {
                p = p->left_child;
            }
            if (p->value == ch)
            {
                found = 1;
                ThreadNode *tmp = p;
                if (p->right_child)
                {
                    if (p->right_tag == PointerTag::THREAD)
                    {
                        succ = p->right_child->value;
                        succ_rtag = (int)p->right_child->right_tag;
                    }
                    else
                    {
                        p = p->right_child;
                        while (p->left_tag == PointerTag::LINK)
                        {
                            p = p->left_child;
                        }
                        succ = p->value;
                        succ_rtag = (int)p->right_tag;
                    }
                }
                else
                {
                    succ = 0;
                }
                p = tmp;
                if (p->left_child)
                {
                    if (p->left_tag == PointerTag::THREAD)
                    {
                        pre = p->left_child->value;
                        pre_ltag = (int)p->left_child->left_tag;
                    }
                    else
                    {
                        p = p->left_child;
                        while (p->right_tag == PointerTag::LINK)
                        {
                            p = p->right_child;
                        }
                        pre = p->value;
                        pre_ltag = (int)p->left_tag;
                    }
                }
                else
                {
                    pre = 0;
                }
                break;
            }
            while (p->right_tag == PointerTag::THREAD && p->right_child)
            {
                p = p->right_child;
                if (p->value == ch)
                {
                    found = 1;
                    ThreadNode *_tmp = p;
                    if (p->right_child)
                    {
                        if (p->right_tag == PointerTag::THREAD)
                        {
                            succ = p->right_child->value;
                            succ_rtag = (int)p->right_child->right_tag;
                        }
                        else
                        {
                            p = p->right_child;
                            while (p->left_tag == PointerTag::LINK)
                            {
                                p = p->left_child;
                            }
                            succ = p->value;
                            succ_rtag = (int)p->right_tag;
                        }
                    }
                    else
                    {
                        succ = 0;
                    }
                    p = _tmp;
                    if (p->left_child)
                    {
                        if (p->left_tag == PointerTag::THREAD)
                        {
                            pre = p->left_child->value;
                            pre_ltag = (int)p->left_child->left_tag;
                        }
                        else
                        {
                            p = p->left_child;
                            while (p->right_tag == PointerTag::LINK)
                            {
                                p = p->right_child;
                            }
                            pre = p->value;
                            pre_ltag = (int)p->left_tag;
                        }
                    }
                    else
                    {
                        pre = 0;
                    }
                    break;
                }
            }
            p = p->right_child;
        }

        if (found)
        {
            std::cout << "succ is ";
            if (succ)
            {
                std::cout << succ << succ_rtag << "\n";
            }
            else
            {
                std::cout << "NULL\n";
            }

            std::cout << "prev is ";
            if (pre)
            {
                std::cout << pre << pre_ltag << "\n";
            }
            else
            {
                std::cout << "NULL\n";
            }
        }
        else
        {
            std::cout << "Not found\n";
        }
        return found;
    }
}; // class ThreadBinaryTree

int main()
{
    ThreadBinaryTree tree;
    tree.traverse_in();
    tree.find();

    return 0;
}