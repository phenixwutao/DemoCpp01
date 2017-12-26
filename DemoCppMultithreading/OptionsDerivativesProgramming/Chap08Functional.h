//  Functional.hpp
#pragma once

#ifndef Functional_hpp
#define Functional_hpp

class SimpleOption {
public:
   // other definitions here
   int daysToExpiration() const { return m_daysToExpiration; }

   double getInTheMoneyProbability(int numDays, double currentUnderlyingPrice) const ;
private:
   int m_daysToExpiration;
};


class OptionComparison {
public:
   OptionComparison(bool directionLess);
   OptionComparison(const OptionComparison &p);
   ~OptionComparison();
   OptionComparison &operator=(const OptionComparison &p);

   bool operator()(const SimpleOption &o1, const SimpleOption &o2);
private:
   bool m_directionLess;
};

void test_compare();
void test_operator();
void test_transform();
void use_bind();
void use_lambda();
void use_lambda2();
void test_use_function();

#endif /* Functional_hpp */
