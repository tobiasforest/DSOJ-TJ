#ifdef __GNUC__
#include <bits/stdc++.h>
#endif // __GNUC__

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#endif // _MSC_VER

#ifdef LOCAL_JUDGE
#include <windows.h>
#include <conio.h>
#endif // LOCAL_JUDGE

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;
typedef int SElemType, *mystack_ptr;

struct MyStack
{
    mystack_ptr base;
    mystack_ptr top;
    size_t size;
    size_t init_stack_capacity = 10;
    const size_t stack_increment = 0;
    MyStack(const size_t s = 10) : base(new SElemType[s]), top(base), size(s), init_stack_capacity(s) {}
    ~MyStack() { delete[] base; }
    SElemType get_top() const { return top == base ? ERROR : *(top - 1); }
    Status push(const SElemType &e)
    {
        if (top - base >= size)
        { // realloc
            return ERROR;
            mystack_ptr new_base = new SElemType[size + stack_increment];
            copy(base, base + size - 1, new_base);
            top = new_base + size;
            size += stack_increment;
            delete[] base;
            base = new_base;
        }
        *top++ = e;
        return OK;
    }
    SElemType pop() { return top == base ? ERROR : *--top; }
    bool empty() const { return base == top; }
};

int main()
{
    size_t stack_size;
    char cmd[10];
    SElemType stack_element;
    cin >> stack_size;
    MyStack ms(stack_size);
    while (true)
    {
        cin >> cmd;
        if (!strcmp("pop", cmd))
        {
            (stack_element = ms.pop()) == ERROR ? cout << "Stack is Empty" << endl : cout << stack_element << endl;
        }
        else if (!strcmp("push", cmd))
        {
            cin >> stack_element;
            if (ms.push(stack_element) == ERROR)
            {
                cout << "Stack is Full" << endl;
            }
        }
        else // if (!strcmp("quit", cmd))
        {
            while (!ms.empty())
            {
                cout << ms.pop() << " ";
            }
            cout << endl;
            break;
        }
    }

    return 0;
}