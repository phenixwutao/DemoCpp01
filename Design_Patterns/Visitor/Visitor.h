#pragma once
#include <iostream>
#include <list>
using namespace std;

namespace VisitorPattern {

  class Visitor;

  // Composite structure
  class Employee {
  public:
    virtual ~Employee();
    virtual void Accept(Visitor& tVisitor) = 0;
    virtual void ShowMyJob() = 0;
    virtual void Add(Employee* tEmployee);
    virtual void Remove(Employee* tEmployee);
    int GetSalary() const;
    const char* GetName();
  protected:
    Employee(const char* name, int money);
  private:
    const char* myName;
    int salary;
  };

  class CEO : public Employee {
  public:
    CEO(const char* name, int money, int tbonus);
    virtual ~CEO();
    virtual void Accept(Visitor& tVisitor) override;
    virtual void ShowMyJob() override;
    virtual void Add(Employee* tEmployee) override;
    virtual void Remove(Employee* tEmployee) override;
    virtual int GetBonus() const;
    int CalculateSalary();
    void ListJob();
  private:
    int bonus;
    list<Employee*>* myEmployeeList;
  };

  class Secretory : public Employee {
  public:
    Secretory(const char* name, int money);
    virtual ~Secretory();
    virtual void Accept(Visitor& tVisitor) override;
    virtual void ShowMyJob() override;
  };

  class CTO : public Employee {
  public:
    CTO(const char* name, int money, int bonus);
    virtual ~CTO();
    virtual void Accept(Visitor& tVisitor) override;
    virtual void ShowMyJob() override;
    virtual void Add(Employee* tEmployee) override;
    virtual void Remove(Employee* tEmployee) override;
    virtual int GetBonus() const;
  private:
    int bonus;
    list<Employee*>* myEmployeeList;
  };

  class Programmer : public Employee {
  public:
    Programmer(const char* name, int money);
    virtual ~Programmer();
    virtual void Accept(Visitor& tVisitor) override;
    virtual void ShowMyJob() override;
  };

  // Class Visitor
  class Visitor {
  public:
    virtual ~Visitor();
    virtual void VisitCEO(CEO*) = 0;
    virtual void VisitCTO(CTO*) = 0;
    virtual void VisitSecretary(Secretory*) = 0;
    virtual void VisitProgrammer(Programmer*) = 0;
  protected:
    Visitor();
  };

  // Concrete Visitor
  class PaymentVisitor : public Visitor {
  public:
    PaymentVisitor();
    virtual ~PaymentVisitor();
    virtual void VisitCEO(CEO*) override;
    virtual void VisitCTO(CTO*) override;
    virtual void VisitSecretary(Secretory*) override;
    virtual void VisitProgrammer(Programmer*) override;
    int GetMoney() const;
    void Reset();
  private:
    int money;
  };

  class JobVisitor : public Visitor {
  public:
    JobVisitor();
    virtual ~JobVisitor();
    virtual void VisitCEO(CEO*) override;
    virtual void VisitCTO(CTO*) override;
    virtual void VisitSecretary(Secretory*) override;
    virtual void VisitProgrammer(Programmer*) override;
  };
  void TestVisitorPattern();
}