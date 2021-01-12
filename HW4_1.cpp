#include <bits/stdc++.h>
using namespace std;

typedef int QElemType;
struct MyQueue
{
protected:
    QElemType *base;
    int front = 0;
    int rear = 0;
    int max_queue_size = 100;

public:
    MyQueue(int s = 100) : base(new QElemType[s]), max_queue_size(s + 1) {}
    ~MyQueue() { delete[] base; }
    int length() const { return (rear - front + max_queue_size) % max_queue_size; }
    bool enqueue(const QElemType &e)
    {
        if ((rear + 1) % max_queue_size == front)
        {
            return false;
        }
        base[rear] = e;
        rear = (rear + 1) % max_queue_size;
        return true;
    }
    QElemType dequeue()
    {
        QElemType result;
        if (front == rear)
        {
            return 0;
        }
        result = base[front];
        front = (front + 1) % max_queue_size;
        return result;
    }
    QElemType top() const { return front == rear ? -1 : base[front]; }
    bool empty() const { return front == rear; }
    void traverse()
    {
        int len = length();
        for (int i = 0; i < len; i++)
        {
            cout << base[(front + i) % max_queue_size] << " ";
        }
        cout << endl;
    }
}; // struct MyQueue

int main()
{
    int size = 0;
    char order[20];
    QElemType tmp;
    cin >> size;
    MyQueue q(size);

    while (true)
    {
        cin >> order;
        if (!strcmp("quit", order))
        {
            q.traverse();
            break;
        }
        else if (!strcmp("dequeue", order))
        {
            q.empty() ? cout << "Queue is Empty" << endl : cout << q.dequeue() << endl;
        }
        else if (!strcmp("enqueue", order))
        {
            cin >> tmp;
            if (!q.enqueue(tmp))
            {
                cout << "Queue is Full" << endl;
            }
        }
        // cout << "Current length: " << q.length() << endl;
    }
    return 0;
}