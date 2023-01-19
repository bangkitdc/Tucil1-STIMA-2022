#include <iostream>
#include <vector>
using namespace std;

bool isValid(string str)
{
    if (str.length() != 1)
    {
        return false;
    }
    else
    {
        if (!isdigit(str[0]))
        {
            if (str[0] != 'A' && str[0] != 'J' && str[0] != 'Q' && str[0] != 'K')
            {
                return false;
            }
        }
        else
        {
            if (str[0] == '0' or str[0] == '1')
            {
                return false;
            }
        }
    }
    return true;
}

int strToNum(string str)
{
    // str pasti A, J, Q, atau K

    if (str[0] == 'A')
    {
        return 1;
    }
    else if (str[0] == 'J')
    {
        return 11;
    }
    else if (str[0] == 'Q')
    {
        return 12;
    }
    else
    { // K
        return 13;
    }
}

void numToChar(int c)
{
    if (c == 1)
    {
        cout << 'A';
    }
    else if (c == 11)
    {
        cout << 'J';
    }
    else if (c == 12)
    {
        cout << 'Q';
    }
    else if (c == 13)
    {
        cout << 'K';
    }
    else
    {
        cout << c;
    }
}

char operators[4] = {'+', '-', '*', '/'};

float func(float a, char op, float b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    default:
        if (b != 0)
        {
            return a / b;
        }
        else
        {
            return -9999;
        }
    }
}

vector<vector<int>> permute(vector<int> &nums)
{
    if (nums.size() <= 1)
    {
        return {nums};
    }

    vector<vector<int>> result;
    for (int i = 0; i < nums.size(); i++)
    {
        vector<int> v(nums.begin(), nums.end());
        v.erase(v.begin() + i);
        auto res = permute(v);

        for (int j = 0; j < res.size(); j++)
        {
            vector<int> _v = res[j];
            _v.insert(_v.begin(), nums[i]);
            result.push_back(_v);
        }
    }
    return result;
}

int main()
{
    /* KAMUS */
    string input[4];
    vector<int> numbers;

    cout << "Enter 4 cards: ";
    cin >> input[0] >> input[1] >> input[2] >> input[3];

    while (!(isValid(input[0]) && isValid(input[1]) && isValid(input[2]) && isValid(input[3])))
    {
        cout << "Invalid" << endl;
        cout << "Enter 4 cards: ";
        cin >> input[0] >> input[1] >> input[2] >> input[3];
    }

    for (int i = 0; i < 4; i++)
    {
        if (isdigit(input[i][0]))
        {
            numbers.push_back(int(input[i][0] - '0'));
        }
        else
        {
            numbers.push_back(strToNum(input[i]));
        }
    }

    int counter = 0;

    vector<vector<int>> permute_numbers = permute(numbers);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int x = 0; x < 24; x++)
                {
                    int a = permute_numbers[x][0];
                    int b = permute_numbers[x][1];
                    int c = permute_numbers[x][2];
                    int d = permute_numbers[x][3];

                    // (N OP N) OP (N OP N)
                    if (func(func(a, operators[i], b), operators[j], func(c, operators[k], d)) == 24)
                    {
                        counter++;
                        cout << "(";
                        numToChar(a);
                        cout << " " << operators[i] << " ";
                        numToChar(b);
                        cout << ") " << operators[j] << " (";
                        numToChar(c);
                        cout << " " << operators[k] << " ";
                        numToChar(d);
                        cout << ")" << endl;
                    }

                    // ((N OP N) OP N) OP N
                    if (func(func(func(a, operators[i], b), operators[j], c), operators[k], d) == 24)
                    {
                        counter++;
                        cout << "((";
                        numToChar(a);
                        cout << " " << operators[i] << " ";
                        numToChar(b);
                        cout << ") " << operators[j] << " ";
                        numToChar(c);
                        cout << ") " << operators[k] << " ";
                        numToChar(d);
                        cout << endl;
                    }

                    // (N OP (N OP N)) OP N
                    if (func(func(a, operators[i], func(b, operators[j], c)), operators[k], d) == 24)
                    {
                        counter++;
                        cout << "(";
                        numToChar(a);
                        cout << " " << operators[i] << " (";
                        numToChar(b);
                        cout << " " << operators[j] << " ";
                        numToChar(c);
                        cout << ")) " << operators[k] << " ";
                        numToChar(d);
                        cout << endl;
                    }

                    // N OP (N OP (N OP N))
                    if (func(a, operators[i], func(b, operators[j], func(c, operators[k], d))) == 24)
                    {
                        counter++;
                        numToChar(a);
                        cout << " " << operators[i] << " "
                             << "(";
                        numToChar(b);
                        cout << " " << operators[j] << " (";
                        numToChar(c);
                        cout << " " << operators[k] << " ";
                        numToChar(d);
                        cout << "))" << endl;
                    }

                    // N OP ((N OP N) OP N)
                    if (func(a, operators[i], func(func(b, operators[j], c), operators[k], d)) == 24)
                    {
                        counter++;
                        numToChar(a);
                        cout << " " << operators[i] << " ((";
                        numToChar(b);
                        cout << " " << operators[j] << " ";
                        numToChar(c);
                        cout << ") " << operators[k] << " ";
                        numToChar(d);
                        cout << ")" << endl;
                    }
                }
            }
        }
    }

    cout << counter << " solutions found" << endl;

    return 0;
}
