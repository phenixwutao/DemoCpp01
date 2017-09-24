#include "StdAfx.h"

//
//  RandomWalkGenerator.cpp
//
//  Simple random walk implementation.

#include <cstdlib>
#include <iostream>
#include <time.h>

#include "Ch02RandomWalkGenerator.h"

using namespace std;

//
// Constructor. The supplied parameters represent the number of elements in the
// random walk, the initial price, and the step size for the random walk.
//
RandomWalkGenerator::RandomWalkGenerator(int size, double start, double step)
  : m_numSteps(size),
  m_stepSize(step),
  m_initialPrice(start)
{
}

RandomWalkGenerator::RandomWalkGenerator(const RandomWalkGenerator &p)
  : m_numSteps(p.m_numSteps),
  m_stepSize(p.m_stepSize),
  m_initialPrice(p.m_initialPrice)
{
}

RandomWalkGenerator::~RandomWalkGenerator()
{
}

RandomWalkGenerator &RandomWalkGenerator::operator=(const RandomWalkGenerator &p)
{
  if (this != &p)
  {
    m_numSteps = p.m_numSteps;
    m_stepSize = p.m_stepSize;
    m_initialPrice = p.m_initialPrice;
  }
  return *this;
}

//
// returns a single step of the random walk
//
double RandomWalkGenerator::computeRandomStep(double currentPrice)
{
  /* initialize random seed: to generate real time random numbers*/
  //time_t t;
  //srand( static_cast<unsigned int>(time(&t)) );
  //srand((unsigned)time(NULL));

  int r = rand() % 3;
  double val = currentPrice;

  // simulate price moving up or down, or remains unchanged
  if (r == 0)
  {
    val += (m_stepSize * val);
  }
  else if (r == 1)
  {
    val -= (m_stepSize * val);
  }
  //printf("random r=%d, price %12.6f\n", r, val);
  return val;
}


//
// This is the main method. It will generate random numbers within
// the constraints set in the constructor.
//
std::vector<double> RandomWalkGenerator::generateWalk()
{
  vector<double> walk;
  double prev = m_initialPrice;

  for (int i = 0; i < m_numSteps; ++i)
  {
    double val = computeRandomStep(prev);
    walk.push_back(val);
    prev = val;
  }
  return walk;
}

