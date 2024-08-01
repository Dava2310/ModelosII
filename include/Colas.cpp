// Implementation of Class Colas
#include "Colas.h"

// Libraries
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor
Colas::Colas(const double lambda, const double miu, const double cost_service, const double cost_wait) 
{   
    // Adding the basic data that exists in every method
    setLambda(lambda);
    setMiu(miu);
    setCost_Service(cost_service);
    setCost_Wait(cost_wait);
}


// Setters
void Colas::setLambda(const double lambda)
{
    if (lambda < 1)
    {
        throw invalid_argument("Lambda must be 1 or more");
    }

    this->lambda = lambda;
}

void Colas::setMiu(const double miu)
{
    if (miu < 1) 
    {
        throw invalid_argument("Miu must be 1 or more");
    }
    
    this->miu = miu;
}

void Colas::setServers(const double servers)
{
    if (servers < 1)
    {
        throw invalid_argument("The amount of servers must be 1 or more");
    }

    this->servers = servers;
}

void Colas::setN(const double N)
{
    if (N < 1)
    {
        throw invalid_argument("N must be 1 or more");
    }

    this->N = N;
}

void Colas::setK(const double K)
{
    if (K < 1)
    {
        throw invalid_argument("K must be 1 or more");
    }

    this->K = K;
}

void Colas::setCost_Service(const double cost_service)
{
    if (cost_service < 0)
    {
        throw invalid_argument("Cost of service can't be a negative number");
    }

    this->cost_service = cost_service;
}

void Colas::setCost_Wait(const double cost_wait)
{
    if (cost_wait < 0)
    {
        throw invalid_argument("Cost of wait can't be a negative number");
    }

    this->cost_wait = cost_wait;
}

void Colas::printData()
{
    cout << "Stability Factor (ro): " << this->ro << endl;
    cout << "P0: " << (this->P0 * 100) << "%" << endl;
    cout << "PW: " << (this->PW * 100) << "%" << endl;
    cout << "PN for " << this->n << " person(s) in the system: " << (this->PN * 100) << "%" <<endl;
    cout << "L: " << this->L << endl;
    cout << "Lq: " << this->LQ << endl;
    cout << "W: " << this->W << endl;
    cout << "Wq: " << this->WQ << endl;
    cout << "L real: " << this->Lr << endl;
    cout << "Lq real: " << this->LQr << endl;
    cout << "CT: " << this->CT << endl;
}
