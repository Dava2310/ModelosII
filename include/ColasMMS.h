#ifndef COLAS_MMS_H
#define COLAS_MMS_H

#include "Colas.h"
#include "Utility.h"
#include <iostream>
#include <cmath>

Utility utility_obj;

using namespace std;

class ColasMMS : public Colas {
public:
    ColasMMS(const double lambda, const double miu, const double cost_service, const double cost_wait, const double servers)
        : Colas(lambda, miu, cost_service, cost_wait) {
            // Llama al constructor de Colas

            setServers(servers);
        } 

    void calculate() override {
        // Implementation of M/M/S model with a Poisson Distribution

        // cout << "Calculating M/M/S data: " << endl;
        // cout << "Servers: " << this->servers << endl;

        // Calculation of Stability (ro)
        this->ro = static_cast<double> (this->lambda / (this->miu * this->servers));
        // cout << "Ro: " << this->ro << endl;

        if (this->ro <= 0 || this->ro >= 1)
        {
            cout << "Stability Factor results in Inestability: " << this->ro << endl;
            return;
        }

        // Calculation of Probabilities
        
        double a = 1;
        for (int i = 1; i < this->servers; i++)
        {
            a += pow(this->lambda / this->miu, i) / utility_obj.factorial(i);
        }

        double b = (pow(this->lambda / this->miu, this->servers)) / utility_obj.factorial(this->servers);
        double c = 1 / (1 - this->ro);

        // cout << "a: " << a << endl;
        // cout << "b: " << b << endl;
        // cout << "c: " << c << endl;

        this->P0 = 1 / (a + (b * c));

        // To calculate PW, we calculate each probabiliy different than P0 until servers - 1
        double probability_no_wait = this->P0;

        for (int n = 1; n < this->servers; n++)
        {
            probability_no_wait += calculatePn(n);
        }

        this->PW = 1 - probability_no_wait;

        cout << "Enter n for Pn: ";
        cin >> this->n;

        this->PN = calculatePn(this->n);

        // Calculation of Client Average
        this->LQ = (this->P0 * pow(this->lambda / this->miu, this->servers) * this->ro) / (utility_obj.factorial(this->servers) * (pow(1 - this->ro, 2)));
        this->L = this->LQ + (this->lambda / this->miu);

        // Calculation of Time Spent Average
        this->WQ = this->LQ / this->lambda;
        this->W = this->WQ + (1 / this->miu);

        // Calculation of Total Costs
        this->CT = (this->cost_service * this->servers) + (this->cost_wait * this->L);
        
        // Calculation for real values of L
        this->LQr = ceil(this->LQ);
        this->Lr = this->LQr + this->servers;
    }

private:
    double calculatePn(const int n) 
    {
        if (n >= 0 && n <= this->servers)
        {
            return (this->P0 * (pow(this->lambda / this->miu, n))) / utility_obj.factorial(n);
        }
        else if (n > this->servers)
        {
            return (this->P0 * (pow(this->lambda / this->miu, n))) / (utility_obj.factorial(this->servers) * pow(this->servers, n - this->servers));
        }

        return 0;
    }

};

#endif