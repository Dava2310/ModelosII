#ifndef COLAS_MM1_H
#define COLAS_MM1_H

#include "Colas.h"
#include <iostream>
#include <cmath>

using namespace std;

class ColasMM1 : public Colas {
public:
    ColasMM1(const double lambda, const double miu, const double cost_service, const double cost_wait)
        : Colas(lambda, miu, cost_service, cost_wait) {} // Llama al constructor de Colas

    void calculate() override {
        // Implementation of M/M/1 model with a Poisson Distribution

        // Calculation of Stability (ro)
        this->ro = static_cast<double> (this->lambda / this->miu);

        if (this->ro <= 0 || this->ro >= 1)
        {
            cout << "Stability Factor results in Inestability: " << this->ro << endl;
            return;
        }

        // Calculation of Probabilities
        this->P0 = 1 - this->ro;
        this->PW = 1 - P0;

        cout << "Enter n for Pn: ";
        cin >> this->n;

        this->PN = pow(this->ro, this->n) * this->P0;

        // Calculation of Client Average
        this->LQ = (pow(this->lambda, 2)) / (this->miu * (this->miu - this->lambda));
        this->L = this->lambda / (this->miu - this->lambda);

        // Calculation of Time Spent Average
        this->WQ = this->lambda / (this->miu * (this->miu - this->lambda));
        this->W = 1 / (this->miu - this->lambda);

        // Calculation of Total Costs
        this->CT = (this->cost_service * this->servers) + (this->cost_wait * this->L);
        
        // Calculation for real values of L
        this->LQr = ceil(this->LQ);
        this->Lr = this->LQr + 1;
    }

};

#endif