#include <bits/stdc++.h>
using namespace std;

class Calculator
{
protected:
    int result = 0;
    char expression[1025];
    stack<int> operand_stack;
    stack<char> operator_stack;

public:
    Calculator(const char e[]) { strcpy(expression, e); }
    int calculate()
    {
        size_t len = strlen(expression) - 1;
        int current_operand = 0;
        expression[len] = ')';
        operator_stack.push('(');
        bool innum = 0;
        for (int cnt = 0; cnt <= len; cnt++)
        {
            if (expression[cnt] == ' ')
            {
                continue;
            }
            if (!isdigit(expression[cnt]) && expression[cnt] != '+' && expression[cnt] != '-' && expression[cnt] != '*' && expression[cnt] != '/' && expression[cnt] != ' ' && expression[cnt] != '(' && expression[cnt] != ')')
            {
                cout << "ERROR" << endl;
                return 1;
            }
            if (isdigit(expression[cnt]))
            {
                current_operand = (current_operand << 1) + (current_operand << 3) + (expression[cnt] ^ 48);
                innum = 1;
            }
            else
            {
                if (innum)
                {
                    operand_stack.push(current_operand);
                    innum = 0;
                }
                current_operand = 0;
                if ((expression[cnt] == '+' || expression[cnt] == '-') && !operator_stack.empty())
                {
                    char current_operator = operator_stack.top();
                    while ((current_operator == '*' || current_operator == '/') && !operator_stack.empty())
                    {
                        operator_stack.pop();
                        int a = operand_stack.top();
                        operand_stack.pop();
                        int b = operand_stack.top();
                        operand_stack.pop();
                        if (current_operator == '*')
                        {
                            operand_stack.push(a * b);
                        }
                        if (current_operator == '/')
                        {
                            if (!b)
                            {
                                cout << "ERROR" << endl;
                                return 1;
                            }
                            operand_stack.push(b / a);
                        }
                        current_operator = operator_stack.top();
                    }
                }
                if (expression[cnt] == ')')
                {
                    char current_operator = operator_stack.top();
                    operator_stack.pop();
                    while (current_operator != '(')
                    {
                        int right = operand_stack.top();
                        operand_stack.pop();
                        int left = operand_stack.top();
                        operand_stack.pop();
                        if (current_operator == '-')
                        {
                            operand_stack.push(left - right);
                        }
                        if (current_operator == '+')
                        {
                            operand_stack.push(left + right);
                        }
                        if (current_operator == '*')
                        {
                            operand_stack.push(left * right);
                        }
                        if (current_operator == '/')
                        {
                            if (!right)
                            {
                                cout << "ERROR" << endl;
                                return 1;
                            }
                            operand_stack.push(left / right);
                        }
                        current_operator = operator_stack.top();
                        operator_stack.pop();
                    }
                }
                else
                {
                    operator_stack.push(expression[cnt]);
                }
            }
        }
        if (!operator_stack.empty())
        {
            cout << "ERROR" << endl;
            return 1;
        }
        result = operand_stack.top();
        return 0;
    }
    int getResult() const { return result; }
};

int main()
{
    char str[1025];
    cin >> str;
    Calculator c(str);
    if (!c.calculate())
    {
        cout << c.getResult() << endl;
    }
    return 0;
}