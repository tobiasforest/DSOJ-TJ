#ifdef __GNUC__
#include <bits/stdc++.h>
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#endif

#include <conio.h>
#include <windows.h>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define NOTFOUND 0
#define INFEASIBLE -1
typedef int Status;
typedef int Boolean;

struct Student
{
    char no[10] = {'\0'};
    char name[100] = {'\0'};
    Student() {} // initialize an empty Student object
    Student(const char _no[], const char _name[])
    {
        strcpy(no, _no);
        strcpy(name, _name);
    }
    ~Student() {}
    Student &operator=(const Student &s)
    {
        strcpy(no, s.no);
        strcpy(name, s.name);
        return *this;
    }
    bool operator==(const Student &s) { return !(strcmp(no, s.no) || strcmp(name, s.name)); }
};
ostream &operator<<(ostream &out, Student &s) { return out << s.no << " | " << s.name; }
istream &operator>>(istream &in, Student &s) { return in >> s.no >> s.name; }

typedef Student ElemType;
const size_t INIT_LIST_SIZE = 100;
const size_t LIST_SIZE_INCREMENT = 20;

struct SqList
{
    ElemType *elem = nullptr;
    size_t length = 0;
    size_t listsize = INIT_LIST_SIZE;
    SqList(const size_t len)
    {
        while (len > listsize)
        {
            listsize += LIST_SIZE_INCREMENT;
        }

        length = len;
        elem = new ElemType[1 + listsize]();

        for (size_t i = 1; i <= length; i++)
        {
            cin >> elem[i];
        }
    }
    ~SqList()
    {
        if (elem)
        {
            delete[] elem;
        }
    }
    Status insert()
    {
        if (!check())
        {
            return ERROR;
        }
        size_t loc = (size_t)-1;
        char loc_s[20] = {'\0'};
        cout << "Please input the location before which you would like to insert an element. If you want to insert it at the end of the list, please just press the enter key: " << endl;
        if (cin.peek() == ' ' || cin.peek() == '\n')
        {
            cin.get();
        }
        cin.getline(loc_s, 1024);
        if (!(loc = atoi(loc_s)))
        {
            loc = length + 1;
        }
        if (loc > length + 1)
        {
            return ERROR;
        }
        if (length == listsize)
        {
            ElemType *_elem = new ElemType[1 + (listsize += LIST_SIZE_INCREMENT)]();
            copy(elem, elem + length + 1, _elem);
            delete[] elem;
            elem = _elem;
        }

        for (size_t i = length; i >= loc; i--)
        {
            elem[i + 1] = elem[i];
        }
        cout << "Please enter the student number and the name of the student to insert: " << endl;
        cin >> elem[loc];
        length++;

        return OK;
    }
    Status searchByNo(char n[])
    {
        if (!check())
        {
            return ERROR;
        }
        Status found = 0;
        for (size_t i = 1; i <= length; i++)
        {
            if (!strcmp(elem[i].no, n))
            {
                cout << i << " " << elem[i] << endl;
                found++;
            }
        }
        return found;
    }
    Status searchByName(char n[])
    {
        if (!check())
        {
            return ERROR;
        }
        Status found = 0;
        for (size_t i = 1; i <= length; i++)
        {
            if (!strcmp(elem[i].name, n))
            {
                cout << "No. | Student Number | Name" << endl;
                cout << i << " | " << elem[i] << endl;
                found++;
            }
        }
        return found;
    }
    Status deleteByNo(char n[])
    {
        if (!check(false))
        {
            return ERROR;
        }
        int count = 0;
        for (size_t i = 1; i <= length; i++)
        {
            if (!strcmp(elem[i].no, n))
            {
                count++;
            }
            else
            {
                elem[i - count] = elem[i];
            }
        }
        length -= count;
        check();
        return count;
    }
    Status deleteByName(char n[])
    {
        if (!check(false))
        {
            return ERROR;
        }
        int count = 0;
        for (size_t i = 1; i <= length; i++)
        {
            if (!strcmp(elem[i].name, n))
            {
                count++;
            }
            else
            {
                elem[i - count] = elem[i];
            }
        }
        length -= count;
        check();
        return count;
    }
    Status distinct()
    {
        if (!check())
        {
            return ERROR;
        }
        for (size_t i = 1; i <= length; i++)
        {
            ElemType &only = elem[i];
            size_t count = 0;
            for (size_t j = i + 1; j <= length; j++)
            {
                if (elem[j] == only)
                {
                    count++;
                }
                else
                {
                    elem[j - count] = elem[j];
                }
            }
            length -= count;
        }
        return OK;
    }
    Status traverse()
    {
        if (!check())
        {
            return ERROR;
        }
        cout << "Student Number | Name" << endl;
        for (size_t i = 1; i <= length; i++)
        {
            cout << elem[i] << endl;
        }
        return OK;
    }
    void _swap(ElemType &e1, ElemType &e2)
    {
        std::swap(e1.name, e2.name);
        std::swap(e1.no, e2.no);
    }
    size_t getPivot(const size_t beg, const size_t end)
    {
        size_t i = beg;
        size_t j = beg + 1;
        for (; j != end; j++)
        { // !there's a segmentation fault
            if (atoi(elem[j].no) < atoi(elem[beg].no))
            {
                _swap(elem[++i], elem[j]);
            }
        }
        _swap(elem[beg], elem[i]);

        return i;
    }
    void quickSort(const size_t beg, const size_t end)
    {
        if (beg != end)
        {
            size_t pivot = getPivot(beg, end);
            quickSort(beg, pivot);
            quickSort(pivot + 1, end);
        }
    }
    Status sort()
    {
        if (!check())
        {
            return ERROR;
        }
        quickSort(1, length + 1);
        return OK;
    }
    bool check(bool flag = true)
    {
        if (flag)
        {
            cout << "There are " << length << " student(s) in the list now." << endl
                 << endl;
        }
        return (bool)length;
    }
};

inline void header()
{
    system("cls");
    cout << "********************************" << endl;
    cout << "*   Student Management System  *" << endl;
    cout << "********************************" << endl;
    return;
}

/*****************************************
 * <_MENU CONTENT_>
 * Command list:
 *     1> Create a student list
 *     2> Insert a student
 *     3> Delete a student
 *     4> Distinguish the student list
 *     5> Sort by student number
 *     6> Display the content of the student list
 *     0> Exit
 * <_END_>
 ****************************************/
inline int menu()
{
    cout << "Command list: " << endl;
    cout << "    1> Create a student list" << endl;
    cout << "    2> Search for a student" << endl;
    cout << "    3> Insert a student" << endl;
    cout << "    4> Delete a student" << endl;
    cout << "    5> Distinguish the student list" << endl;
    cout << "    6> Sort by student number" << endl;
    cout << "    7> Display the content of the student list" << endl;
    cout << "    0> Exit" << endl;

    cout << endl
         << "Please enter your order: ";
    return _getche() - '0';
}

inline void wait_for_press()
{
    cout << endl
         << "Press any key to continue...";
    (void)_getch();
    return;
}

int main()
{
    SqList *l = nullptr;
    while (true)
    {
        system("cls");
        header();
        int order = menu();
        Status num = 0;
        size_t len = 0;
        char str[100] = {'\0'};
        header();

        switch (order)
        {
        case 0: // exit
            if (l)
            {
                delete l;
            }
            cout << endl
                 << "Program ending..." << endl;
            Sleep(1000);
            exit(0);
            break;
        case 1: // create list
            cout << "1> Create a student list" << endl
                 << endl;
            cout << "Please enter the length of the student list: ";
            cin >> len;
            cout << endl
                 << "Please enter student numbers and names of the " << len << " students relatively: " << endl;
            if (l)
            {
                delete l;
                l = nullptr;
            }
            if ((l = new SqList(len)))
            {
                cout << endl
                     << "Student list is created successfully!" << endl;
            }
            else
            {
                cerr << endl
                     << "Something went wrong. Please try again. " << endl;
            }
            break;
        default:
            if (!l)
            {
                cerr << "The SqList does not exist. Please try again. " << endl;
                break;
            }
            switch (order)
            {
            case 2:
                cout << "2> Search for a student" << endl
                     << endl;
                cout << "    1> Search by student number" << endl
                     << "    2> Search by student name" << endl
                     << "    0> Go back to previous menu" << endl
                     << "Please input your order: ";
                switch (_getche() - '0')
                {
                case 0: // return
                    break;
                case 1: // number
                    cout << endl
                         << "Please enter the student number: ";
                    cin >> str;
                    num = l->searchByNo(str);
                    cout
                        << "There are " << num << " students found." << endl;
                    break;
                case 2: // name
                    cout << endl
                         << "Please enter the student name: ";
                    cin >> str;
                    num = l->searchByName(str);
                    cout
                        << "There are " << num << " students found." << endl;
                    break;
                default: // illegal
                    cerr << "Wrong input. Please try again." << endl;
                    break;
                }

                break;
            case 3: // insert
                cout << "3> Insert a student" << endl
                     << endl;
                if (l->insert())
                {
                    cout << endl
                         << "The student was inserted successfully! " << endl;
                }
                else
                {
                    cerr << endl
                         << "The location you input is illegal. Please try again. " << endl;
                }
                break;
            case 4: // delete
                cout << "4> Delete a student" << endl
                     << endl;
                cout << "    1> Delete by student number" << endl
                     << "    2> Delete by student name" << endl
                     << "    0> Go back to previous menu" << endl
                     << "Please input your order: ";
                switch (_getche() - '0')
                {
                case 0: // return
                    break;
                case 1: // number
                    cout << endl
                         << "Please enter the student number: ";
                    cin >> str;
                    if (l->deleteByNo(str))
                    {
                        cout << endl
                             << "The student whose number is " << str << " was successfully deleted. " << endl;
                    }
                    else
                    {
                        cerr << endl
                             << "The student whose number is " << str << " was not found. " << endl;
                    }
                    break;
                case 2: // name
                    cout << endl
                         << "Please enter the student name: ";
                    cin >> str;
                    if (l->deleteByName(str))
                    {
                        cout << endl
                             << "The student named " << str << " was successfully deleted. " << endl;
                    }
                    else
                    {
                        cerr << endl
                             << "The student named " << str << " was not found. " << endl;
                    }
                    break;
                default: // illegal
                    cerr << "Wrong input. Please try again." << endl;
                    break;
                }
                break;
            case 5: // distiguish
                cout << "5> Distinguish the student list" << endl
                     << endl;
                l->distinct();
                cout << "The list is distinguished successfully! " << endl;
                break;
            case 6: // sort
                cout << "6> Sort the student list" << endl
                     << endl;
                l->sort();
                cout << "The list is sorted successfully! " << endl;
                break;
            case 7: // display
                cout << "7> Display the student list" << endl
                     << endl;
                if (l)
                {
                    l->traverse();
                }
                break;
            default: // illegal
                cerr << "Your input is not legal. Please try again. " << endl;
                break;
            }
        }
        wait_for_press();
    }
    return 0;
}