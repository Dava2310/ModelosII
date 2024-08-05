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
#include "include/ColasMMK1.h"
#include "include/ColasMMKS.h"

using namespace std;

// Macro methods for Forecasts, Queues and Inventory Models
void forecasts();
void queues();
void inventory();
void menu();

Utility utility;

int main()
{
    // Menu of Options
    cout << "This program is a help for the Modelos II subject!" << endl << endl;
    menu();
    cout << "Thanks for using this program! By: Dava2310" << endl << endl;
    system("pause");
}

void menu()
{
    
    int option = 0;
    do
    {
        system("pause");
        system("cls");
        // Items of the Menu
        cout << "\t\t MENU" << endl << endl;
        cout << "1- Calculate Queues" << endl;
        cout << "2- Calculate Forecasts" << endl;
        cout << "3- Calculate Inventory" << endl;
        cout << "4- Exit" << endl << endl;

        option = utility.getInt("Insert a valid option between 1 and 4: ");

        switch (option)
        {
        case 1:
            queues();
            break;
        case 2:
            forecasts();
            break;
        case 3:
            inventory();
            break;
        case 4:
            return;
            break;
        default:
            cout << "Chose an option between 1 and 4" << endl << endl;
            break;
        }

    } while (option != 4);
    
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
                return;
            }
            // MMS method
            else 
            {
                Colas *modelo = new ColasMMS(static_cast<double>(lambda), static_cast<double>(miu), cost_service, cost_wait, static_cast<double>(servers));
                modelo->calculate();

                cout << "Results for M/M/S model: " << endl << endl;
                modelo->printData();

                delete modelo;
                return;
            }
        }
        else if (method == 2)
        {
            return;
        }
        else 
        {
            // MMK1 Model
            if (servers == 1)
            {
                Colas* modelo = new ColasMMK1(static_cast<double>(lambda), static_cast<double>(miu), cost_service, cost_wait, static_cast<double>(K));
                modelo->calculate();

                cout << "Results for M/M/K/1 model: " << endl << endl;
                modelo->printData();

                delete modelo;
                return;
            }
            // MMKS Model
            else 
            {
                Colas* modelo = new ColasMMKS(static_cast<double>(lambda), static_cast<double>(miu), cost_service, cost_wait, static_cast<double>(K), servers);
                modelo->calculate();

                cout << "Results for M/M/K/S model: " << endl << endl;
                modelo->printData();

                delete modelo;
                return;
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
