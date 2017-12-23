#include "StdAfx.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

#include "Ch01GenericOption.h"
#include "Ch02RandomWalkGenerator.h"
#include "OptionsDerivatives.h"
#include "Date.h"

using namespace std;

static unsigned int iPass = 1;
void OptionsDerivTestRandomWalks()
{
  printf("----------------------------- Pass %d ---> \"%s\"\n", iPass++, __func__);
  RandomWalkGenerator rw(100, 30, 0.01);
  vector<double> walk = rw.generateWalk();
  for (size_t i = 0; i<walk.size(); ++i)
  {
    if ((i+1) % 5)
      cout << "step " << setw(2) << i << "  " << setw(10) << setprecision(6) << walk[i] << " ";
    else
      cout << "step " << setw(2) << i << "  " << setw(10) << setprecision(6) << walk[i] << "\n";
  }
  cout << endl;
}

void OptionsDerivTestValueOptions()
{
  printf("----------------------------- Pass %d ---> \"%s\"\n", iPass++, __func__);
  GenericOption option(100.0, OptionType_Put, 1.1);
  double price1 = 120.0;
  double value = option.valueAtExpiration(price1);
  cout << " For 100PUT, value at expiration for price " << price1 << " is " << value << endl;
  double price2 = 85.0;
  value = option.valueAtExpiration(price2);
  cout << " For 100PUT, value at expiration for price " << price2 << " is " << value << endl;

  auto limit = 120.0;
  for (auto price = 80.0; price <= limit; price += 0.2)
  {
    value = option.profitAtExpiration(price);
    cout << price << ", " << value << endl;
  }
}

void OptionsDerivTestDate()
{
  Date d(2015, 9, 12);
  DayOfTheWeek wd = d.dayOfTheWeek();
  cout << "day of the week: " << wd << " " << d.dayOfWeek() << endl;
  d.print();

  d.add(25);
  d.print();

  d.addTradingDays(120);
  d.print();
  cout << "day of the week: " << d.dayOfTheWeek() << " " << d.dayOfWeek() << endl;
}
