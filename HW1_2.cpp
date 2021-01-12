#ifdef __GNUC__
#include <bits/stdc++.h>
#endif

#ifdef _MSC_VER
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#endif

using namespace std;

int main()
{
    vector<int> l;
    int num = 0;
    int tmp = 0;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> tmp;
        l.push_back(tmp);
    }

    for (auto i = l.begin(); i - l.begin() < num; i++)
    {
        tmp = *i;

        for (auto j = i + 1; j - l.begin() < num;)
        {
            if (tmp == *j)
            {
                j = l.erase(j);
                num--;
                continue;
            }
            j++;
        }
    }

    for (auto &i : l)
    {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}