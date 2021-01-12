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

#define EQ(a, b) !strcmp(a, b)
#define LEN(key) strlen(key)
#define EVL(dst, src) strcpy(dst, src)
#define NULLKEY nullptr
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define LOVERFLOW -1

using namespace std;

int isprime(const int n)
{
    if (n <= 1)
    {
        return 0;
    }
    int threshold = (int)sqrt(n);
    for (int i = 2; i <= threshold; i++)
    {
        if (!(n % i))
        {
            return 0;
        }
    }
    return 1;
}

int nextPrime(const int cur)
{
    for (int i = cur; true; i++)
    {
        if (isprime(i))
        {
            return i;
        }
    }
    return 0;
}

typedef struct Element ElemType;
typedef int Status;
typedef char KT, *KeyType;

struct Element
{
    KeyType key = NULLKEY;
    int length() const { return strlen(key); }
    Element() {}
    Element(const KeyType &k) : key(new KT[strlen(k) + 1]) { EVL(key, k); }
    ~Element() { delete[] key; }
    Element &operator=(const Element &e)
    {
        if (key)
        {
            delete[] key;
            key = nullptr;
        }
        key = new KT[LEN(e.key) + 1];
        EVL(key, e.key);
        return *this;
    }
}; // struct Element

class HashTable
{
private:
    int size = 0;
    int count = 0; // count of elements
    ElemType *elem = nullptr;

    int quadradic_probing_index(const int t)
    {
        return (t % 2) ? (int)pow((t + 1) / 2, 2) : -(int)pow(t / 2, 2);
    }

    Status collision(int &p, int &c)
    {
        p += quadradic_probing_index(++c);
        p %= size;
        if (p < 0)
        {
            p += size;
        }
        return OK;
    }

public:
    HashTable(const int N, const int P) : size(nextPrime(P)), elem(new ElemType[size])
    {
        for (int i = 0; i < N; i++)
        {
            int p;
            KT key[1000] = {'\0'};
            cin >> key;
            if (insert(key, p))
            {
                if (EQ(elem[p].key, key))
                {
                    cout << p << " ";
                }
                else
                {
                    cout << "- ";
                }
            }
            else
            {
                cout << "- ";
            }
        }
    }

    ~HashTable() { delete[] elem; }

    int hash(const KeyType &key)
    {
        int len = LEN(key), h = key[0];
        for (int i = 1; i < len; i++)
        {
            h *= 37;
            h %= size;
            h += key[i];
            h %= size;
        }
        h %= size;
        if (h < 0)
        {
            h += size;
        }

        return h;
    }

    Status search(const KeyType &key, int &p, int &c)
    {
        int q = p = hash(key);
        while (elem[p].key != NULLKEY) // && !EQ(key, elem[p].key))
        {
            p = q;
            if (c == size)
            {
                return LOVERFLOW;
            }
            collision(p, c);
        }
        if (p >= 0)
        {
            return elem[p].key == NULLKEY ? FALSE : TRUE;
        }
        else
        {
            return LOVERFLOW;
        }
    }

    Status insert(const ElemType &e, int &p)
    {
        int c = 0, v = 0;
        if (TRUE == (v = search(e.key, p, c)))
        {
            elem[p] = e;
            count++;
            return LOVERFLOW; // existed
        }
        else if (LOVERFLOW == v)
        {
            return ERROR;
        }
        else // if (c < size)
        {
            elem[p] = e;
            count++;
            return OK;
        }
    }

}; // class HashTable

int main()
{
    freopen("out.txt", "r", stdin);
    int a, b;
    cin >> a >> b;
    HashTable ht(a, b);
    return 0;
}