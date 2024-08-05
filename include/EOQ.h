#ifndef EOQ_H
#define EOQ_H

using namespace std;

#include <string>

class EOQ
{
private:
    // Basic Data
    double Q;                   // The amount of Inventory
    double D;                   // Demand
    double L;                   // Reestablishment Time
    double i;                   // Interest per unit
    double P;                   // Price of each item
    
    // To calculate
    double T;                   // Time of the Inventory
    double N;                   // Order Average per time
    double R;                   // Reorder Point

    // Costs
    double CO;                  // Orden Cost
    double co;                  // Unit Orden Cost
    
    double CA;                  // Adquisition Cost

    double CH;                  // Storage Cost
    double ch;                  // Unit Storage Cost

    double CT;                  // Total Cost

    // Adittional Data
    double S;                   // Amount of Missing Units
    double CS;                  // Cost of Missing Units
    double cs;                  // Unit Cost of Missing Units
    double Imax;                // Maximum Real Inventory
    double T1, T2;              // Times for EOQ with Missing Units
public:
    EOQ(const double D, const double i, const double P, const double co);
    EOQ(const double D, const double ch, const double co);
    ~EOQ();
    // Setters
    void setD(const double);
    void setL(const double);
    void setI(const double);
    void setP(const double);
    void setCo(const double);
    void setCh(const double);
    void setCs(const double);
    virtual void calculate() = 0; // Abstract Method to Override in each model
};

EOQ::EOQ(const double D, const double i, const double P, const double co)
{
    // Adding the basic data that exsits in every model
    setD(D);
    setI(i);
    setP(P);
    setCo(co);
}

EOQ::EOQ(const double D, const double ch, const double co)
{
    // Adding the basic data that exsits in every model
    setD(D);
    setCh(ch);
    setCo(co);
}

EOQ::~EOQ()
{ 
}


#endif