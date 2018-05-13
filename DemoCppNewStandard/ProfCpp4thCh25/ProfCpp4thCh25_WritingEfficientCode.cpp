#include "stdafx.h"
#include "ProfCpp4thCh25_WritingEfficientCode.h"

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

class Person
{
public:
  Person();
  Person(string_view firstName, string_view lastName, int age);
  Person(const Person& rhs);
  virtual ~Person();

  string_view getFirstName() const { return mFirstName; }
  string_view getLastName() const { return mLastName; }
  int getAge() const { return mAge; }

private:
  string mFirstName, mLastName;
  int mAge = 0;
};

Person::Person()
{
  cout << "Person Default Ctor" << endl;
}

Person::Person(string_view firstName, string_view lastName, int age)
  : mFirstName(firstName), mLastName(lastName), mAge(age)
{
  cout << "Person Ctor" << endl;
}

Person::~Person()
{
  cout << "Person Dtor" << endl;
}

Person::Person(const Person& rhs)
  : mFirstName(rhs.mFirstName), mLastName(rhs.mLastName), mAge(rhs.mAge)
{
  cout << "Person Copy ctor" << endl;
}

ostream& operator<<(ostream& ostr, const Person& p)
{
  ostr << p.getFirstName() << " " << p.getLastName() <<
    " " << p.getAge() << endl;

  return ostr;
}

void processPerson(const Person& /*p*/)
{
  // process the person
}

Person createPerson()
{
  Person newP("Marc", "Gregoire", 38);
  return newP;
}

namespace chap25
{
  void chap25DemoPersonObject()
  {
    FUNC_INFO;
    Person me("Marc", "Gregoire", 38);
    processPerson(me);

    cout << "-----" << endl;

    cout << createPerson();

    cout << "-----" << endl;

    createPerson();
  }
}
