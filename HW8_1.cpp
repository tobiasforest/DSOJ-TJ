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
#include <queue>
#endif

#define ERROR 0
#define OK 1
#define LOVERFLOW -1

typedef int Status;
typedef int KeyType;
typedef int SElemType;

using namespace std;

class SSTable
{
protected:
    int length = -1;
    SElemType *elem = nullptr;

public:
    SSTable(const int l) : length(l), elem(new SElemType[l])
    {
        for (int i = 0; i < length; i++)
        {
            scanf("%d", &elem[i]);
        }
    }
    ~SSTable() { delete[] elem; }
    int binarySearch(const KeyType &key)
    {
        int low = 0, high = length - 1, mid;
        while (low < high)
        {
            mid = ((high + low) >> 1);
            if (key == elem[mid])
            {
                high = mid;
            }
            else if (key > elem[mid])
            {
                low = mid + 1;
            }
            else // if (key < elem[mid])
            {
                high = mid - 1;
            }
        }
        return key == elem[high] ? high : LOVERFLOW;
    }
}; // class SSTable

int main()
{
    freopen("input8_1.txt", "rb", stdin);
    int size;
    KeyType key;
    scanf("%d", &size);

    SSTable t(size);
    scanf("%d", &size);
    while (size--)
    {
        scanf("%d", &key);
        printf("%d\n", t.binarySearch(key));
    }
    return 0;
}