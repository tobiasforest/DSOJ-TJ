/**********************************
 * @date   12/30/2020
 * @author 林日中 (1951112)
 * @file   HW9_4_generate_data.cpp
 **********************************/
#if defined(__GNUC__)
#include <bits/stdc++.h>
#elif defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <ctime>
#include <iomanip>
#include <queue>
#endif

using namespace std;

int generate_random_data()
{
    int count = 0;
    string address;
    fstream out;

    {
        count = 10;
        address = "input1.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        while (count--)
        {
            out << rand() << ' ';
        }
        out << endl;

        out.close();
    }

    {
        count = 100;
        address = "input2.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        while (count--)
        {
            out << rand() << ' ';
        }
        out << endl;

        out.close();
    }

    {
        count = 1000;
        address = "input3.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        while (count--)
        {
            out << rand() << ' ';
        }
        out << endl;

        out.close();
    }

    {
        count = 10000;
        address = "input4.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        while (count--)
        {
            out << rand() << ' ';
        }
        out << endl;

        out.close();
    }

    {
        count = 100000;
        address = "input5.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        while (count--)
        {
            out << rand() << ' ';
        }
        out << endl;

        out.close();
    }

    {
        count = 1000000;
        address = "input6.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        while (count--)
        {
            out << rand() << ' ';
        }
        out << endl;

        out.close();
    }

    {
        count = 10000;
        address = "input7.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        int *arr = new int[count];
        for (int i = 0; i < count; i++)
        {
            arr[i] = rand();
        }
        sort(arr, arr + count);

        for (int i = 0; i < count; i++)
        {
            out << arr[i] << ' ';
        }
        out << endl;

        delete[] arr;
        out.close();
    }

    {
        count = 10000;
        address = "input8.txt";

        out.open(address, ios::out | ios::binary);
        out << count << endl;

        int *arr = new int[count];
        for (int i = 0; i < count; i++)
        {
            arr[i] = rand();
        }
        sort(arr, arr + count);

        for (int i = count - 1; i >= 0; i--)
        {
            out << arr[i] << ' ';
        }
        out << endl;

        delete[] arr;
        out.close();
    }

    return 0;
}

int main()
{
    srand((unsigned)time(nullptr));
    generate_random_data();
}