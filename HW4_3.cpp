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
#include <queue>
#endif // _MSC_VER
#include <windows.h>
using namespace std;

typedef struct MyMessage
{
private:
    char *content = nullptr;
    char time_str[32] = {'\0'};
    time_t t;
    time_t get_time()
    {
        t = time(nullptr);
        // locale::global(locale("en.US-utf8"));
        std::strftime(time_str, sizeof(time_str), "%A %c", std::localtime(&t));
        return t;
    }
    friend istream &operator>>(istream &, MyMessage &);
    friend ostream &operator<<(ostream &, const MyMessage &);

public:
    MyMessage() {}
    MyMessage(const char *c)
    {
        if (c)
        {
            content = new char[strlen(c) + 1];
            strcpy(content, c);
        }
        get_time();
    }
    MyMessage(const MyMessage &m)
    {
        if (m.content)
        {
            content = new char[strlen(m.content) + 1];
            strcpy(content, m.content);
        }
        get_time();
    }
    ~MyMessage()
    {
        if (content)
        {
            delete[] content;
            content = nullptr;
        }
    }
    MyMessage &set(const char *c)
    {
        delete[] content;
        content = nullptr;
        if (c)
        {
            content = new char[strlen(c) + 1];
            strcpy(content, c);
        }
        get_time();
        return *this;
    }
    MyMessage &operator=(const MyMessage &m)
    {
        if (content)
        {
            delete[] content;
            content = nullptr;
        }
        if (m.content)
        {
            content = new char[strlen(m.content) + 1];
            strcpy(content, m.content);
        }
        get_time();
        return *this;
    }
    const char *get_content() const { return content; }
    operator bool() const { return content != nullptr; }
} QElemType; // struct MyMessage
istream &operator>>(istream &in, MyMessage &m)
{
    if (m.content)
    {
        delete[] m.content;
        m.content = nullptr;
    }
    char tmp[1024] = {'\0'};
    in >> tmp;
    m.content = new char[strlen(tmp) + 1];
    strcpy(m.content, tmp);
    return in;
}
ostream &operator<<(ostream &out, const MyMessage &m)
{
    return out << "Content : " << (m.content ? m.content : "<empty>") << std::endl
               << "Time    : " << m.time_str;
}

struct MyQueue
{
protected:
    QElemType *base = nullptr;
    int _size = 0;
    int front = 0;
    int rear = 0;
    int max_queue_size = 0;

public:
    MyQueue(const int s = 100) : base(new QElemType[s]), max_queue_size(s) {}
    ~MyQueue() { delete[] base; }
    int size() const { return _size; } // = (rear - front + max_queue_size) % max_queue_size;
    bool push(const QElemType &e)
    {
        if ((rear + 1) % max_queue_size == front)
        {
            return false;
        }
        base[rear] = e;
        rear = (rear + 1) % max_queue_size;
        _size++;
        return true;
    }
    QElemType pop()
    {
        QElemType result;
        if (front == rear)
        {
            return QElemType();
        }
        result = base[front];
        front = (front + 1) % max_queue_size;
        _size--;
        return result;
    }
    int pop(MyQueue &q, int n = -1)
    {
        if (n == -1 || n > (q.max_queue_size - q.size() - 1) || n > this->size())
        {
            n = min(this->size(), q.max_queue_size - q.size() - 1);
        }
        for (int i = n; i; i--)
        {
            if (this->top())
            {
                q.push(this->pop());
            }
        }
        return n;
    }
    QElemType top() const { return front == rear ? QElemType() : base[front]; }
    bool empty() const { return front == rear; }
    bool full() const { return _size == max_queue_size; }
    void traverse()
    {
        int len = size();
        for (int i = 0; i < len; i++)
        {
            cout << base[(front + i) % max_queue_size] << endl;
        }
    }
}; // struct MyQueue

int test_myqueue(const int total, int cap_a, int cap_b)
{
    cout << "\n<<< This is a test function >>>\n\n";
    int message_capacity = 60000, messages_per_sec = 6000, seq = 0, count = total;
    MyQueue notice_queue(message_capacity + 1), a(cap_a + 1), b(cap_b + 1);
    clock_t start = clock();

    do
    {
        if (seq < total)
        { // generate elements of notice queue
            char str[] = "hello world - ?????";
            for (int i = 0; i < messages_per_sec && seq < total; i++, seq++)
            {
                sprintf(str, "hello world - %05i", seq);
                notice_queue.push(str);
            }
        }
        if (!notice_queue.empty())
        {
            notice_queue.pop(a);
        }
        if (!notice_queue.empty())
        {
            notice_queue.pop(b);
        }
        if (!a.empty())
        {
            cout << "a.pop() : \n"
                 << a.pop() << endl;
            count--;
        }
        if (!b.empty())
        {
            cout << "b.pop() : \n"
                 << b.pop() << endl
                 << endl;
            count--;
        }
        while (!a.empty())
        {
            a.pop();
            count--;
        }
        while (!b.empty())
        {
            b.pop();
            count--;
        }
        Sleep(1000);
    } while (count > 0);
    cout << "The process ended in " << (double)(clock() - start) / CLOCKS_PER_SEC << " second(s). " << endl;
    return 0;
}

int main()
{
    cout << "Welcome! This program is committed to realizing the process of two sub-queues grabbing messages from a main notification queue. " << endl
         << "There is a main notification queue generating 6,000 messages per second, totally 60,000. Please enter the capacities of the two queues within [2000..3000]: ";

    int cap_a, cap_b;
    cin >> cap_a >> cap_b;

    test_myqueue(60000, cap_a, cap_b);
    system("pause");
    return 0;
}