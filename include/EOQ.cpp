// Implementation of Class EOQ
#include "EOQ.h"

// Libraries
#include <iostream>
#include <stdexcept>

using namespace std;

// Setters
void EOQ::setP(const double P)
{
    if (P <= 0)
    {
        throw invalid_argument("Price can't be either 0 or negative");
    }

    this->P = P;
}

void EOQ::setI(const double I)
{
    if (I <= 0)
    {
        throw invalid_argument("Interest can't be either 0 or negative");
    }

    this->i = I;
}

void EOQ::setL(const double L)
{
    if (L <= 0)
    {
        throw invalid_argument("L (replenishment time) can't be either 0 or negative");
    }

    this->L = L;
}

void EOQ::setCh(const double ch)
{
    if (ch <= 0)
    {
        throw invalid_argument("Ch (Unit Storage Cost) can't be either 0 or negative");
    }

    this->ch = ch;
}

void EOQ::setCo(const double co)
{
    if (co <= 0)
    {
        throw invalid_argument("Co (Unit Order Cost) can't be either 0 or negative");
    }

    this->co = co;
}

void EOQ::setCs(const double cs)
{
    if (cs <= 0)
    {
        throw invalid_argument("Cs (Unit Missing Cost) can't be either 0 or negative");
    }

    this->cs = cs;
}

void EOQ::setD(const double D)
{
    if (D <= 0)
    {
        throw invalid_argument("D (Demand) can't be either 0 or negative");
    }

    this->D = D;
}

