//
//  MathFunction.cpp
#include "StdAfx.h"
#include "Chap10MathFunction.h"

#include <iostream>

using std::cout;
using std::endl;


PolynomialFunction::PolynomialFunction(const std::vector<double> &coef)
: m_coeficients(coef)
{
}

PolynomialFunction::PolynomialFunction(const PolynomialFunction &p)
: m_coeficients(p.m_coeficients)
{
}

PolynomialFunction::~PolynomialFunction()
{
}

PolynomialFunction &PolynomialFunction::operator=(const PolynomialFunction &p)
{
    if (this != &p)
    {
        m_coeficients = p.m_coeficients;
    }
    return *this;
}

double PolynomialFunction::operator()(double x)
{
    auto n = m_coeficients.size();
    double y = 0;
    size_t i = 0;
    for (i=0; i<n-1; ++i)
    {
        y += m_coeficients[i];
        y *= x;
    }
    if (i < n) {
        y += m_coeficients[i];
    }
    return y;
}

void test_polufunction()
{
    PolynomialFunction f( { 1, 0, 0 } );

    double begin = -2, end = 2;
    double step = (end - begin) / 100.0;
    for (int i=0; i<100; ++i)
    {
        cout <<  begin + step * i << ", ";
    }
    cout << endl;
    for (int i=0; i<100; ++i)
    {
        cout << f( begin + step * i) << ", ";
    }
}
