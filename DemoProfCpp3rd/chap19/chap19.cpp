#include "stdafx.h"

#include "chap19.h"
#include <iostream>

#include <functional>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

void func(int num, const string& str)
{
  cout << "func(" << num << ", " << str.c_str() << ")" << endl;
}
bool isEven(int num)
{
  bool fEven = (num % 2 == 0);
  printf("process num %d IsEven: %c\n", num, fEven == true ? 'Y' : 'N');
  return fEven;
}

/********************************************************************
* test std::function
********************************************************************/
void chap19StdFunction()
{
  function<void(int, const string&)> f1 = func;
  f1(1, "test");
  auto f2 = func;
  f2(2, "hello");

  vector<int> vec(10);
  std::iota(vec.begin(), vec.end(), 0);

  std::function<bool(int)> f3 = isEven;
  auto wCount = count_if(cbegin(vec), cend(vec), f3);
  cout << wCount << " even numbers" << endl;
}

void process(const vector<int>& vec, std::function<void(int)> f)
{
  for (const auto& i : vec)
  {
    f(i);
  }
}
void printNum(int num)
{
  cout << num << " ";
}

/********************************************************************
* test std::function and Lambda expression
********************************************************************/
void chap19StdFunctionLambda()
{
  vector<int> vec(10);
  std::iota(vec.begin(), vec.end(), 0);
  process(vec, printNum);
  int sum(0);
  process(vec, [&sum](int num) {sum += num; } );
  cout << "sum = " << sum << endl;
}
