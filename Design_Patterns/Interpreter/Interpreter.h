#pragma once

#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

namespace InterpreterPattern
{
  class ChineseExp {
  public:
    ChineseExp();
    virtual ~ChineseExp();
    virtual double Interprete(map<string, int> myDict) = 0; // Here use map to implement the Context
  };

  class ChineseNum : public ChineseExp {
  public:
    virtual ~ChineseNum();
    ChineseNum(string num);
    virtual double Interprete(map<string, int> myDict);
  private:
    string numString;
  };

  class ChineseAdd : public ChineseExp {
  public:
    virtual ~ChineseAdd();
    ChineseAdd(ChineseExp* left, ChineseExp* right);
    virtual double Interprete(map<string, int> myDict);
  private:
    ChineseExp * leftOperator;
    ChineseExp* rightOperator;
  };


  class ChineseSub : public ChineseExp {
  public:
    virtual ~ChineseSub();
    ChineseSub(ChineseExp* left, ChineseExp* right);
    virtual double Interprete(map<string, int> myDict);
  private:
    ChineseExp * leftOperator;
    ChineseExp* rightOperator;
  };

  class ChineseMul : public ChineseExp {
  public:
    virtual ~ChineseMul();
    ChineseMul(ChineseExp* left, ChineseExp* right);
    virtual double Interprete(map<string, int> myDict);
  private:
    ChineseExp * leftOperator;
    ChineseExp* rightOperator;
  };

  class ChineseDiv : public ChineseExp {
  public:
    virtual ~ChineseDiv();
    ChineseDiv(ChineseExp* left, ChineseExp* right);
    virtual double Interprete(map<string, int> myDict);
  private:
    ChineseExp * leftOperator;
    ChineseExp* rightOperator;
  };

  // Class Evaluator, construct the syntax tree
  // This is not the part of Interpreter Pattern
  class Evaluator {
  public:
    virtual ~Evaluator();
    Evaluator();
    void Construct(string expression);
    double Interprete(map<string, int> myDict);
  private:
    ChineseExp * myExpression;
    ChineseExp* ExpConstruct(stack<string>* numStack);
    int IsNumber(string tString);
  };
  void TestInterpreterPattern();
}
