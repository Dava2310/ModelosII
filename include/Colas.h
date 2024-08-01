#ifndef COLAS_H
#define COLAS_H

using namespace std;

#include <string>
#include <vector>

class Colas{

    // Atributes
    protected:
        // Basic Data
        double lambda;         // The rate of incoming clients in clients per time
        double miu;            // The rate of service in clients per time
        double servers = 1;    // The amount of servers in the system, default amount is 1
        double N;              // The known amount of clients in total (Finite People, Finite Queue)
        double K;              // The limit of clients than can be in the system (Infinite People, Finite Queue)
        // int method;         // This represent the method of Queue implemented (1 - Infinite People, Infinite Queue, 2- Finite People, Finite Queue, 3- Infinite People, Finite Queue)
        double cost_service;// This represents the unit cost of service per server 
        double cost_wait;   // This represents the unit cost of wait in the whole system
        // To Calculate for every model
        double ro;                // This represents stability
        // Probabilities
        double P0;                // The probability of the system to be empty
        double PW;                // The probability of a client to wait in the system when it arrives
        double PN;                // The probability of N clients to be on the system
        int n;                    // The amount of N clients to calculate PN
        // Clients in the System
        double L;                 // The amount of client in the system
        double LQ;                // The amount of clientes in the queue
        int Lr;
        int LQr;
        // Times
        double W;                 // The amount of time that a client spends in the system
        double WQ;                // The amount of time that a client spends in the queue (WQ < W)!
        // Costs
        double CT;                // The total amount of costs that this model represents to the company
    public:
        Colas(const double lambda, const double miu, const double cost_service, const double cost_wait); //Constructor
        // Setters
        void setLambda(const double);
        void setMiu(const double);
        void setServers(const double);
        void setN(const double);
        void setK(const double);
        void setCost_Service(const double);
        void setCost_Wait(const double);
        void printData();
        // Getters
        int getLambda();
        // Other methods
        // Calculate Method
        virtual void calculate() = 0; // Abstract Method to Override in each model
};
#endif