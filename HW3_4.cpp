#ifdef __GNUC__
#include <bits/stdc++.h>
#endif // __GNUC__
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#endif // _MSC_VER

using namespace std;

struct MyData
{
    int data;
    // int returnAddress // only needed for linked stacks
    MyData(const int n = 0) : data(n) {}
    int get() const { return data; }
    int set(const int n) { return data = n; }
    MyData &operator=(const int n)
    {
        data = n;
        return *this;
    }
    operator int() const { return data; }
}; // struct MyData

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;
typedef MyData SElemType, *mystack_ptr;

struct MyStack
{
    mystack_ptr base; // pointer of data segment; !*DO NOT CHANGE ITS VALUE!*
    mystack_ptr top;
    size_t capacity;
    size_t init_capacity = 10;
    const size_t stack_increment = 50;
    MyStack(const size_t s = 10) : base(new SElemType[s]), top(base), capacity(s), init_capacity(s) {}
    ~MyStack() { delete[] base; }
    SElemType get_top() const { return top == base ? MyData() : *(top - 1); }
    SElemType push(const SElemType &e)
    {
        if ((size_t)(top - base) >= capacity)
        { // realloc
            mystack_ptr new_base = new SElemType[capacity + stack_increment];
            copy(base, base + capacity - 1, new_base);
            top = new_base + capacity;
            capacity += stack_increment;
            delete[] base;
            base = new_base;
        }
        *top++ = e;
        return SElemType(e);
    }
    SElemType pop() { return top == base ? SElemType(ERROR) : *--top; }
    int empty() const { return base == top; }
    int get_size() const { return top - base; }
}; // struct MyStack

// test the functions of struct MyStack
long long test_mystack()
{
    // initialize the stack
    cout << "Welcome! This function is committed to calculating the sum of numbers from 1 to a particular number. " << endl
         << "Please enter a positive integer: ";
    int num = 0;
    cin >> num;
    MyStack s(num);

    // push elements
    for (int i = 1; i <= num; i++)
    {
        s.push(MyData(i));
    }
    cout << "Current size of my stack : " << s.get_size() << endl;

    // pop elements and sum them
    long long sum = 0; // sum of stack elements popped
    for (int i = 0; i < num; i++)
    {
        sum += s.pop().get();
    }
    cout << "The sum of integers within [1.." << num << "] : " << sum << endl;
    return sum;
}

int main()
{
    test_mystack();
    return 0;
}