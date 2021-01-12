/********************************
 * @date   12/30/2020
 * @author 林日中 (1951112)
 * @file   HW9_4.cpp
 ********************************/
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

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define LOVERFLOW -1
#define MAX_SIZE 1000
#define NULL_RECORD nullptr
#define NULL_KEY 0
#define EQ(a, b) (a == b)
#define LT(a, b) (a < b)
#define LE(a, b) (a <= b)
#define EVL(a, b) (a = b)

typedef int KeyType;
typedef struct Element RecordType;

struct Element
{
    KeyType key;
    Element(const KeyType &k = NULL_KEY) : key(k) {}
    Element(const Element &e) : key(e.key) {}
    Element &operator=(const Element &e)
    {
        EVL(key, e.key);
        return *this;
    }
}; // struct Element

bool comp(const Element &l, const Element &r)
{
    return LT(l.key, r.key);
}

void swap(Element &l, Element &r)
{
    Element temp = r;
    r = l;
    l = temp;
}

class SqList
{
protected:
    RecordType *original = nullptr;
    RecordType *r = nullptr;
    RecordType *correct = nullptr;
    int length = 0;

    void recover()
    {
        copy(original, original + length + 1, r);
    }

    void output_to_file(ofstream &out)
    {
        for (int i = 1; i <= length; i++)
        {
            out << r[i].key << " ";
        }
        out << endl;
    }

    bool check_accuracy()
    {
        RecordType *pr = r + 1, *pc = correct + 1;
        while (pr - r <= length && EQ((pr++)->key, (pc++)->key))
            ;
        return (pr - r == length + 1);
    }

    void shell_insert(const int dk)
    {
        for (int i = dk + 1, j; i <= length; i++)
        {
            if (LT(r[i].key, r[i - dk].key))
            {
                r[0] = r[i];
                // j = i - dk : equivalently in each group, j = i - 1
                // j -= dk    : equivalently in each group, j--
                // j > 0      : if j <= 0, the insert pos is found
                for (j = i - dk; j > 0 && LT(r[0].key, r[j].key); j -= dk)
                { // elements move backwards
                    r[j + dk] = r[j];
                }
                r[j + dk] = r[0];
            }
        }
    }

    void shell_sort(const int delta[], const int t)
    {
        for (int k = 0; k < t; k++)
        {
            shell_insert(delta[k]);
        }
    }

    int partition(int low, int high)
    {
        r[0] = r[low];
        KeyType pivot_key = r[low].key;
        while (low < high)
        {
            while (low < high && r[high].key >= pivot_key)
            {
                high--;
            }
            r[low] = r[high];
            while (low < high && r[low].key <= pivot_key)
            {
                low++;
            }
            r[high] = r[low];
        }
        r[low] = r[0];
        return low;
    }

    void qsort(int low, int high)
    {
        if (low < high)
        {
            auto pivot_loc = partition(low, high);
            qsort(low, pivot_loc - 1);
            qsort(pivot_loc + 1, high);
        }
    }

    void heap_adjust(int s, const int m)
    {
        RecordType rc = r[s]; // save r[s]
        // traverse root to leaves in s
        // j = 2 * s : j = s->left_child
        // j *= 2    : j = j->left_child

        int father = s;
        int child = father * 2;

        for (int j = 2 * s; j <= m; j *= 2)
        {
            if (j < m && LT(r[j].key, r[j + 1].key))
            { // if right child is bigger, choose it (max heap)
                j++;
            }
            if (!LT(rc.key, r[j].key))
            {
                break;
            }
            r[s] = r[j]; // root = bigger one between two children
            s = j;       // s becomes root of the child
        }
        r[s] = rc;
    }

    // merge [L..M], [M+1..H] the two ordered sequences into one
    void merge(RecordType *SR, RecordType *&TR,
               const int L, const int M, const int H)
    {
        int i = L, j = M + 1, k = L;
        while (i <= M && j <= H) // while two sequences are both not traversed completely
        {
            if (LT(SR[i].key, SR[j].key))
            {
                TR[k++] = SR[i++]; // smaller one into TR, move forward
            }
            else
            {
                TR[k++] = SR[j++]; // smaller one into TR, move forward
            }
        }

        while (i <= M) // merge remain of the sequence into result
        {
            TR[k++] = SR[i++];
        }
        while (j <= H) // merge remain of the sequence into result
        {
            TR[k++] = SR[j++];
        }
    }

    void merge_pass(RecordType *SR, RecordType *&TR,
                    const int len, const int n)
    {
        int i;

        // loop when lengths of two subsequences are both n
        for (i = 1; i + 2 * len - 1 <= n; i += 2 * len)
        {
            merge(SR, TR, i, i + len - 1, i + 2 * len - 1);
        }

        if (i + len - 1 < n) // two subsequences, length of latter one < len
        {
            merge(SR, TR, i, i + len - 1, n);
        }
        else // only one subsequence
        {
            while (i <= n)
            {
                TR[i] = SR[i];
                i++;
            }
        }
    }

    void merge_sort(RecordType *R, const int n)
    {
        int len = 1;
        RecordType *R1 = new RecordType[n + 1];

        while (len < n)
        {
            merge_pass(R, R1, len, n);
            len *= 2;
            merge_pass(R1, R, len, n);
            len *= 2;
        }

        delete[] R1;
    }

public:
    SqList(const int l)
        : original(new RecordType[l + 1]),
          r(new RecordType[l + 1]),
          correct(new RecordType[l + 1]),
          length(l)
    {
        for (int i = 1; i <= l; i++)
        {
            cin >> original[i].key;
        }
        copy(original, original + length + 1, correct);
        sort(correct + 1, correct + length + 1, comp);
        recover();
    }

    ~SqList()
    {
        delete[] original;
        delete[] r;
        delete[] correct;
    }

    void Display()
    {
        for (int i = 1; i <= length; i++)
        {
            cout << r[i].key << " ";
        }
        cout << "\n";
    }

    /************************************
     * Sort Name        : Insertion Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(n^2)
     ************************************/
    void InsertSort()
    {
        for (int i = 2, j; i <= length; i++)
        {
            if (LT(r[i].key, r[i - 1].key))
            {
                r[0] = r[i]; // set a sentinel, avoid overflow
                r[i] = r[i - 1];
                for (j = i - 2; LT(r[0].key, r[j].key); j--)
                {
                    r[j + 1] = r[j];
                }
                r[j + 1] = r[0]; // r[i] is already covered
            }
        }
    }

    /*******************************************
     * Sort Name        : Binary Insertion Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(n^2)
     *******************************************/
    void BinaryInsertSort()
    {
        for (int i = 2; i <= length; i++)
        {
            r[0] = r[i];
            int low = 1;
            int high = i - 1;
            while (low <= high)
            {
                int mid = (low + high) >> 1;
                if (LT(r[0].key, r[mid].key))
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            // until now, we have found the insert pos: [high + 1] or [low]

            for (int j = i - 1; j >= high + 1; j--)
            { // elements move backwards
                r[j + 1] = r[j];
            }
            r[high + 1] = r[0]; // r[i] has been covered
        }
    }

    /********************************************
     * Sort Name        : Shell Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(n^1.3 ~ n^1.5)
     * Parameters       :
     *       - delta[]  : increment sequence,
     *                    last element must be 1
     *       - t        : length of delta
     ********************************************/
    void ShellSort()
    {
        int delta[] = {5, 3, 1};
        shell_sort(delta, sizeof(delta) / sizeof(int));
    }

    /*********************************
     * Sort Name        : Bubble Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(n^2)
     *********************************/
    void BubbleSort()
    {
        int change_flag = 1;
        for (int i = length; change_flag && i >= 2; i--)
        {
            change_flag = 0;
            for (int j = 1; j < i; j++)
            {
                if (LT(r[j + 1].key, r[j].key))
                {
                    swap(r[j + 1], r[j]);
                    change_flag = 1;
                }
            }
        }
    }

    /********************************
     * Sort Name        : Quick Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(nlog_2n)
     ********************************/
    void QuickSort()
    {
        qsort(1, length);
    }

    /************************************
     * Sort Name        : Selection Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(n^2)
     ************************************/
    void SelectSort()
    {
        for (int i = 1; i < length; i++)
        {
            int m = i;
            for (int j = i + 1; j <= length; j++)
            { // find minimum pos in [i..n]
                if (LT(r[j].key, r[m].key))
                {
                    m = j;
                }
            }
            if (m != i)
            {
                swap(r[i], r[m]);
            }
        }
    }

    /********************************
     * Sort Name        : Heap Sort
     * Space Complexity : O(1)
     * Time Complexity  : O(nlog2_n)
     ********************************/
    void HeapSort()
    {
        for (int i = length / 2; i > 0; i--)
        { // loop from last non-leaf node to root, we get initial heap
            heap_adjust(i, length);
        }
        for (int i = length; i > 1; i--) // i == 1 is root
        {
            swap(r[1], r[i]);
            heap_adjust(1, i - 1); // first (i - 1) elements adjusted to heap
        }
    }

    /********************************
     * Sort Name        : Merge Sort
     * Space Complexity : O(n)
     * Time Complexity  : O(nlog2_n)
     ********************************/
    void MergeSort()
    {
        merge_sort(r, length);
    }

    void TestSort(ofstream &out,
                  const string &sort_name,
                  void (SqList::*func)())
    {
        clock_t begin_time = clock();
        (this->*func)();
        clock_t end_time = clock();
        out << "Sort name : " << sort_name << endl
            << "Time cost : " << fixed << setprecision(3) << (double)(end_time - begin_time) / CLOCKS_PER_SEC << "s" << endl
            << "Accuracy  : " << (check_accuracy() ? "Y" : "N") << endl
            << "Status    : Complete" << endl
            << endl;
        recover();
    }

    void Test(ofstream &out)
    {
        TestSort(out, "Insertion Sort", &SqList::InsertSort);
        TestSort(out, "Binary Insertion Sort", &SqList::BinaryInsertSort);
        TestSort(out, "Shell Sort", &SqList::ShellSort);
        TestSort(out, "Bubble Sort", &SqList::BubbleSort);
        TestSort(out, "Quick Sort", &SqList::QuickSort);
        TestSort(out, "Selection Sort", &SqList::SelectSort);
        TestSort(out, "Heap Sort", &SqList::HeapSort);
        TestSort(out, "Merge Sort", &SqList::MergeSort);
    }

}; // class SqList

void SqListDebug(const string &in_file_name,
                 const string &out_file_name,
                 ofstream &out_file)
{
    int count_of_elements;

    if (out_file.is_open())
    {
        out_file.close();
    }

    freopen(in_file_name.c_str(), "rb", stdin);
    out_file.open(out_file_name, ios::out | ios::binary);
    cin >> count_of_elements;
    SqList sqlist(count_of_elements);

    out_file << "*************" << endl
             << "PROGRAM BEGIN" << endl
             << "*************" << endl
             << endl;

    out_file << "INPUTFILE : " << in_file_name << endl
             << "OUTPUTFILE: " << out_file_name << endl
             << "COUNT     : " << count_of_elements << endl
             << endl;

    sqlist.Test(out_file);

    out_file << "****************" << endl
             << "PROGRAM COMPLETE" << endl
             << "****************" << endl;

    out_file.close();
}

int main()
{
    ofstream out;
    SqListDebug("input1.txt", "output1.txt", out);
    SqListDebug("input2.txt", "output2.txt", out);
    SqListDebug("input3.txt", "output3.txt", out);
    SqListDebug("input4.txt", "output4.txt", out);
    SqListDebug("input5.txt", "output5.txt", out);
    SqListDebug("input6.txt", "output6.txt", out);
    SqListDebug("input7.txt", "output7.txt", out);
    SqListDebug("input8.txt", "output8.txt", out);

    return 0;
}
