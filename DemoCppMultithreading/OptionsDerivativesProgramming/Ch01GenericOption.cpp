#include "StdAfx.h"

#include <iostream>

//  GenericOption.cpp

#include "Ch01GenericOption.h"

#include <iostream>

using std::cout;
using std::endl;

GenericOption::GenericOption(double strike, OptionType type, double cost)
: m_strike(strike), m_type(type), m_cost(cost)
{
}

GenericOption::GenericOption(const GenericOption &p)
: m_strike(p.m_strike), m_type(p.m_type), m_cost(p.m_cost)
{
}

GenericOption::~GenericOption()
{
}

GenericOption &GenericOption::operator=(const GenericOption &p)
{
    if (this != &p)
    {
        m_type = p.m_type;
        m_strike = p.m_strike;
        m_cost = p.m_cost;
    }
    return *this;
}

//
// Computes the value of the option at expiration date.
// Value depends on the type of option (CALL or PUT) and strike.
//
double GenericOption::valueAtExpiration(double underlyingAtExpiration)
{
    double value = 0.0;

    if (m_type == OptionType_Call)
    {
        if (m_strike < underlyingAtExpiration)
        {
            value = underlyingAtExpiration - m_strike;
        }
    }
    else  // it is an OptionType_Put
    {
        if (m_strike > underlyingAtExpiration)
        {
            value = m_strike - underlyingAtExpiration;
        }
    }
    return value;
}

//
// return the profit (value at expiration minus option cost)
//
double GenericOption::profitAtExpiration(double underlyingAtExpiration)
{

    double finalValue = valueAtExpiration(underlyingAtExpiration);

    return finalValue - m_cost;
}
