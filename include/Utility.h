#ifndef UTILITY_H
#define UTILITY_H

using namespace std;

#include <limits>
#include <iostream>
#include <stdexcept>

class Utility
{

public:
    // Get a Valid Integer
    int getInt(const string &prompt)
    {
        int value;
        while (true)
        {
            cout << prompt;
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Not a valid integer. Try Again." << endl;
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

    // Get a Valid Double
    double getDouble(const string &prompt)
    {
        double value;
        while (true)
        {
            cout << prompt;
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Not a valid decimal number. Try Again." << endl;
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

    string getMethod(const int method)
    {
        string message = "";

        if (method == 1)
        {
            message = "Infinite Population, Infinite Queue";
        }
        else if (method == 2)
        {
            message = "Finite Population, Finite Queue";
        }
        else
        {
            message = "Infinite Population, Finite Queue";
        }

        return message;
    }

    double factorial(const int n)
    {
        double factorial = 1.0;

        if (n < 0) 
        {
            throw invalid_argument("Factorial of negative number doesn't exist");
        }

        for (int i = 1; i <= n; i++)
        {
            factorial *= i;
        }

        return factorial;
    }
};

#endif