#include "StdAfx.h"

#include <vector>
#include <iostream>
#include <iomanip>

#include "Ch01GenericOption.h"
#include "RandomWalkGenerator.h"
#include "OptionsDerivatives.h"

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
