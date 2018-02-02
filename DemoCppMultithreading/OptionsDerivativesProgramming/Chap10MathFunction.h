#pragma once
//  MathFunction.h

#ifndef MathFunction_hpp
#define MathFunction_hpp

#include <stdio.h>
#include <vector>


class MathFunction {
public:
  // this just an interface
  virtual ~MathFunction() {}
  virtual double operator()(double x) = 0;
};


//
//  Polynomial has the form  c_1 x^n + c_2 x^n-1 + ....  + c_n-1 x^1 + c_n
class PolynomialFunction : public MathFunction
{
public:
    PolynomialFunction(const std::vector<double> &coef);
    PolynomialFunction(const PolynomialFunction &p);
    virtual ~PolynomialFunction();
    PolynomialFunction &operator=(const PolynomialFunction &p);

    virtual double operator()(double x) override;

private:
    std::vector<double> m_coeficients;
};


#endif /* MathFunction_hpp */
