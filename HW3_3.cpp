#include <bits/stdc++.h>
using namespace std;

class Station
{
protected:
    int len;
    char in_seq[1024];

public:
    Station(const char *i) : len(strlen(i)) { strcpy(in_seq, i); }
    bool checkStackOrder(const char *out_seq) const
    {
        stack<char> q;
        int index = 0, i = 0;
        for (i = 0; i < len;)
        {
            if (!q.empty() && out_seq[i] == q.top())
            {
                q.pop();
                i++;
            }
            else
            {
                if (index < len)
                {
                    q.push(in_seq[index++]);
                }
                else
                {
                    break;
                }
            }
        }
        return i == len ? true : false;
    }
}; // class Station

int main()
{
    char seq[1024];
    cin >> seq;
    Station s(seq);

    while (cin >> seq)
    {
        cout << (s.checkStackOrder(seq) ? "yes" : "no") << endl;
    }
    return 0;
}