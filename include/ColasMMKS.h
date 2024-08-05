#ifndef COLAS_MMKS_H
#define COLAS_MMKS_H

#include "Colas.h"
#include "Utility.h"
#include <iostream>
#include <cmath>

Utility util;

using namespace std;

class ColasMMKS : public Colas
{

private:
    /* data */

    double calculatePn(const int n)
    {

        double probability = 0;

        if (n >= this->servers && n <= this->K)
        {
            probability = ((pow(this->lambda / this->miu, n)) / (util.factorial(n))) * this->P0;
            return probability;
        }
        else if (n >= 1 && n <= (this->servers - 1))
        {
            probability = ((pow(this->lambda / this->miu, n)) / (util.factorial(this->servers) * pow(this->servers, n - this->servers))) * this->P0;
            return probability;
        }
        else if (n > this->K)
        {
            probability = 0;
            return probability;
        }

        return probability;
    }

public:
    ColasMMKS(const double lambda, const double miu, const double cost_service, const double cost_wait, const double K, const double servers)
        : Colas(lambda, miu, cost_service, cost_wait)
    {
        setK(K);
        setServers(servers);
    }

    void calculate() override
    {
        // Implementation of M/M/K/S Model

        // Calculation of Stability (ro)
        this->ro = this->lambda / (this->servers * this->miu);

        // Calculation of Probabilities

        // Calculation for P0

        if (this->K <= this->servers)
        {
            double a = 1;

            for (int i = 1; i < this->K; i++)
            {
                a += (pow(this->lambda / this->miu, i)) / util.factorial(i);
            }

            this->P0 = 1 / a;
        }
        else
        {
            double a = 1;

            for (int i = 1; i < this->servers; i++)
            {
                a += pow(this->lambda / this->miu, i) / util.factorial(i);
            }

            double b = (pow(this->lambda / this->miu, this->servers)) / util.factorial(this->servers);
            double c = (1 - pow(this->ro, this->K + 1)) / (1 - this->ro);

            this->P0 = 1 / (a + (b * c));
        }

        // Calculation of PW
        // To calculate PW, we calculate each probability different than P0 until servers - 1
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

        // Calculation of LQ
        double y = this->P0 * pow(this->lambda / this->miu, this->servers) * this->ro;
        double z = util.factorial(this->servers) * pow(1 - this->ro, 2);

        double x = (1 - pow(this->ro, this->K - this->servers) - ((this->K - this->servers) * pow(this->ro, this->K - this->servers) * (1 - this->ro)));
        this->LQ = (y / z) * x;

        // Calculation of L
        double l, u = 0;

        for (int n = 0; n < this->servers; n++)
        {
            l += (n * calculatePn(n)) + this->LQ + this->servers;
        }

        for (int n = 0; n < this->servers; n++)
        {
            u += calculatePn(n);
        }

        this->L = l * (1 - u);

        // Calculation of Time Spent Average
        this->WQ = this->LQ / this->lambda;
        this->W = this->L / this->lambda;

        // Calculation of Total Costs
        this->CT = (this->cost_service * this->servers) + (this->cost_wait * this->L);

        // Calculation for real values of L
        this->LQr = ceil(this->LQ);
        this->Lr = this->LQr + this->servers;
    }
};

#endif