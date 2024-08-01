// Libraries
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>

// Class Libraries
#include "include/Colas.h"
#include "include/Utility.h"
#include "include/ColasMM1.h"
#include "include/ColasMMS.h"

using namespace std;

// Macro methods for Forecasts, Queues and Inventory Models
void forecasts();
void queues();
void inventory();

Utility utility;

int main()
{
    system("cls");
    queues();
    system("pause");
}

void queues()
{
    // Basic Data Variables
    int lambda, miu, servers, N, K, method;
    double cost_service, cost_wait;
    bool confirmation = false;
    char confirmation_message;

    // Gathering data
    lambda = utility.getInt("Enter Lambda (Arrival Rate): ");
    miu = utility.getInt("Enter Miu (Service Rate): ");
    servers = utility.getInt("Enter Amount of Servers: ");
    cost_service = utility.getDouble("Enter Unit Service Cost: ");
    cost_wait = utility.getDouble("Enter Unit Waiting Cost: ");

    // Method
    string message = "\nEnter Method. \n";
    message.append("1- Infinite Population, Infinite Queue\n");
    message.append("2- Finite Population, Finite Queue\n");
    message.append("3- Infinite Population, Finite Queue\n");
    message.append("\nMethod: ");

    do
    {
        method = utility.getInt(message);
    } while (method < 1 || method > 3);

    if (method == 2)
    {
        N = utility.getInt("Enter N (Population): ");
    }
    else if (method == 3)
    {
        K = utility.getInt("Enter K (Queue Limit): ");
    }

    // Printing values for post user verification
    cout << "\nVerify your data." << endl
         << endl;
    cout << "Lambda: " << lambda << endl;
    cout << "Miu: " << miu << endl;
    cout << "Servers: " << servers << endl;
    cout << "Unit Service Cost: " << cost_service << endl;
    cout << "Unit Waiting Cost: " << cost_wait << endl;

    message = "Selected Method: ";
    message.append(utility.getMethod(method));

    if (method == 2)
    {
        cout << "N (Population): " << N << endl;
    }
    else if (method == 3)
    {
        cout << "K (Queue Limit): " << K << endl;
    }

    cout << "\nConfirm Data (Y/N): ";
    cin >> confirmation_message;

    if (!(tolower(confirmation_message) == 'y'))
    {
        return;
    }

    // In case user wants to continue with the calculation
    // We proceed to create the object

    try
    {
        if (method == 1)
        {
            // MM1 method
            if (servers == 1)
            {
                Colas *modelo = new ColasMM1(static_cast<double>(lambda), static_cast<double>(miu), cost_service, cost_wait);
                modelo->calculate();

                cout << "Results for M/M/1 model: " << endl << endl;
                modelo->printData();

                delete modelo;
            }
            // MMS method
            else 
            {
                Colas *modelo = new ColasMMS(static_cast<double>(lambda), static_cast<double>(miu), cost_service, cost_wait, static_cast<double>(servers));
                modelo->calculate();

                cout << "Results for M/M/S model: " << endl << endl;
                modelo->printData();

                delete modelo;
                
            }
        }

    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const out_of_range &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Unkown Error." << endl;
    }
}

void forecasts()
{
}

void inventory()
{
}
