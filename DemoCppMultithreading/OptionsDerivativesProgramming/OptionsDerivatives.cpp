#include "StdAfx.h"

#include <vector>
#include <iostream>
#include <iomanip>

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
