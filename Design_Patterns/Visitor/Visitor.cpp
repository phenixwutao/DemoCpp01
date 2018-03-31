#include "StdAfx.h"
#include "Visitor.h"

namespace VisitorPattern {

  // Class Employee
  Employee::~Employee()
  {
  }

  Employee::Employee(const char* name, int money) : myName(name), salary(money)
  {
  }

  int Employee::GetSalary() const
  {
    return salary;
  }

  const char* Employee::GetName()
  {
    return myName;
  }

  void Employee::Add(Employee* tEmployee)
  {
  }

  void Employee::Remove(Employee* tEmployee)
  {
  }

  // Class CEO
  CEO::CEO(const char* name, int money, int tbonus) : Employee(name, money), bonus(tbonus)
  {
    myEmployeeList = new list<Employee*>;
  }

  CEO::~CEO()
  {
    delete myEmployeeList;
  }

  void CEO::Accept(Visitor& tVisitor)
  {
    for (auto& it : *myEmployeeList)
    {
      it->Accept(tVisitor);
    }
    tVisitor.VisitCEO(this);
  }

  void CEO::ShowMyJob()
  {
    cout << Employee::GetName() << ": Manager the company (CEO)!" << endl;
  }

  void CEO::Add(Employee* tEmployee)
  {
    myEmployeeList->push_back(tEmployee);
  }

  void CEO::Remove(Employee* tEmployee)
  {
    myEmployeeList->remove(tEmployee);
  }

  int CEO::GetBonus() const
  {
    return bonus;
  }

  int CEO::CalculateSalary()
  {
    PaymentVisitor payment;
    this->Accept(payment);
    return(payment.GetMoney());
  }

  void CEO::ListJob()
  {
    JobVisitor showJob;
    this->Accept(showJob);
  }

  // Class Secretory
  Secretory::Secretory(const char* name, int money) : Employee(name, money)
  {
  }

  Secretory::~Secretory()
  {
  }

  void Secretory::Accept(Visitor& tVisitor)
  {
    tVisitor.VisitSecretary(this);
  }

  void Secretory::ShowMyJob()
  {
    cout << Employee::GetName() << ": Paper works (Secretory)!" << endl;
  }

  // Class CTO
  CTO::CTO(const char* name, int money, int tbonus) : Employee(name, money), bonus(tbonus)
  {
    myEmployeeList = new list<Employee*>;
  }

  CTO::~CTO()
  {
    delete myEmployeeList;
  }

  void CTO::Accept(Visitor& tVisitor)
  {
    for (auto& it : *myEmployeeList)
    {
      it->Accept(tVisitor);
    }
    tVisitor.VisitCTO(this);
  }

  void CTO::ShowMyJob()
  {
    cout << Employee::GetName() << ": Manager the project (CTO)!" << endl;
  }

  void CTO::Add(Employee* tEmployee)
  {
    myEmployeeList->push_back(tEmployee);
  }

  void CTO::Remove(Employee* tEmployee)
  {
    myEmployeeList->remove(tEmployee);
  }

  int CTO::GetBonus() const
  {
    return bonus;
  }

  // Class Programmer
  Programmer::Programmer(const char* name, int money) : Employee(name, money)
  {
  }

  Programmer::~Programmer()
  {
  }

  void Programmer::Accept(Visitor& tVisitor)
  {
    tVisitor.VisitProgrammer(this);
  }

  void Programmer::ShowMyJob()
  {
    cout << Employee::GetName() << ": programming (Programmer)!" << endl;
  }

  //class Visitor
  Visitor::Visitor()
  {
  }

  Visitor::~Visitor()
  {
  }

  // class PaymentVisitor

  PaymentVisitor::PaymentVisitor() : money(0)
  {
  }

  PaymentVisitor::~PaymentVisitor()
  {
  }

  void PaymentVisitor::VisitCEO(CEO* tCEO)
  {
    money += tCEO->GetSalary() + tCEO->GetBonus();
  }

  void PaymentVisitor::VisitCTO(CTO* tCTO)
  {
    money += tCTO->GetSalary() + tCTO->GetBonus();
  }

  void PaymentVisitor::VisitSecretary(Secretory* tSecretory)
  {
    money += tSecretory->GetSalary();
  }

  void PaymentVisitor::VisitProgrammer(Programmer* tProgrammer)
  {
    money += tProgrammer->GetSalary();
  }

  int PaymentVisitor::GetMoney() const
  {
    return money;
  }

  void PaymentVisitor::Reset()
  {
    money = 0;
  }

  // class JobVisitor
  JobVisitor::JobVisitor()
  {
  }

  JobVisitor::~JobVisitor()
  {
  }

  void JobVisitor::VisitCEO(CEO* tCEO)
  {
    tCEO->ShowMyJob();
  }

  void JobVisitor::VisitCTO(CTO* tCTO)
  {
    tCTO->ShowMyJob();
  }

  void JobVisitor::VisitSecretary(Secretory* tSecretory)
  {
    tSecretory->ShowMyJob();
  }

  void JobVisitor::VisitProgrammer(Programmer* tProgrammer)
  {
    tProgrammer->ShowMyJob();
  }

  void TestVisitorPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    CEO* myCEO = new CEO("Jobs", 1, 100000);
    CTO* myCTO = new CTO("Woz", 10000, 50000);
    Secretory* mySecretary1 = new Secretory("Lisa", 4000);
    Secretory* mySecretary2 = new Secretory("Jane", 4000);
    Programmer* myProgrammer1 = new Programmer("Mike", 6000);
    Programmer* myProgrammer2 = new Programmer("Rose", 5000);
    Programmer* myProgrammer3 = new Programmer("Tom", 6000);
    myCEO->Add(myCTO);
    myCEO->Add(mySecretary1);
    myCEO->Add(mySecretary2);
    myCTO->Add(myProgrammer1);
    myCTO->Add(myProgrammer2);
    myCTO->Add(myProgrammer3);
    myCEO->ListJob();
    cout << myCEO->CalculateSalary() << endl;

    delete myCEO;
    delete myCTO;
    delete mySecretary1;
    delete mySecretary2;
    delete myProgrammer1;
    delete myProgrammer2;
    delete myProgrammer3;
  }
}