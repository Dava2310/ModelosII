#ifndef COLAS_MMK1_H
#define COLAS_MMK1_H

#include "Colas.h"
#include "Utility.h"
#include <iostream>
#include <cmath>

using namespace std;

class ColasMMK1 : public Colas
{
private:
    /* data */
public:
    ColasMMK1(const double lambda, const double miu, const double cost_service, const double cost_wait, const double K)
        : Colas(lambda, miu, cost_service, cost_wait) {
            // Llama al constructor de Colas

            setK(K);
        } 
    ~ColasMMK1();

    void calculate() override 
    {
        // Implementation of M/M/K/1 Model

        // Calculation of Stability (ro)
        this->ro = this->lambda / this->miu;

        // Calculation of Probabilities
        this->P0 = (1 - this->ro) / (1 - pow(this->ro, this->K + 1));
        this->PW = 1 - this->P0;

        cout << "Enter n for Pn: ";
        cin >> this->n;

        if (this->n > this->K)
        {
            this->PN = 0;
        }
        else
        {
            this->PN = ( (1 - this->ro) / (1 - pow(this->ro, this->K + 1)) ) * pow(this->ro, this->n);
        }

        double a = this->ro / (1 - this->ro);
        double b = (this->K + 1) * (pow(this->ro, this->K + 1));
        double c = 1 - pow(this->ro, this->K + 1);

        // Calculation of Client Average
        this->L = a - (b / c);
        this->LQ = this->L - (1 - this->P0);

        // Calculation of Time Spent Average
        this->WQ = this->LQ / this->lambda;
        this->W = this->L / this->lambda;

        // Calculation of Total Costs
        this->CT = (this->cost_service * this->servers) + (this->cost_wait * this->L);

        // Calculation for real values of L
        this->LQr = ceil(this->LQ);
        this->Lr = this->LQr + 1;
    }
};

ColasMMK1::~ColasMMK1()
{
}


#endif