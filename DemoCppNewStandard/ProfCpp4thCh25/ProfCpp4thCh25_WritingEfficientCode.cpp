#include "stdafx.h"
#include "ProfCpp4thCh25_WritingEfficientCode.h"
#include "ObjectPool.h"
#include "NameDB.h"

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

namespace chap25
{
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

  void chap25DemoPersonObject()
  {
    FUNC_INFO;
    Person me("Marc", "Gregoire", 38);
    processPerson(me);

    cout << "-----" << endl;

    cout << createPerson(); // call insertion operator

    cout << "-----" << endl;

    createPerson();
  }

  class ExpensiveObject
  {
  public:
    ExpensiveObject() { mID = ++msCount; cout << "ctor " << mID << endl; }
    virtual ~ExpensiveObject() { cout << "dtor " << mID << endl; }

    // Methods to populate the object with specific information.
    // Methods to retrieve the object data.
    // (not shown)

  private:
    int mID;
    static int msCount;
    // Other data members (not shown)
  };
  int ExpensiveObject::msCount = 0;

  ObjectPool<ExpensiveObject>::Object
    getExpensiveObject(ObjectPool<ExpensiveObject>& pool)
  {
    // Obtain an ExpensiveObject object from the pool.
    auto object = pool.acquireObject();

    // Populate the object. (not shown)

    return object;
  }

  void processExpensiveObject(ObjectPool<ExpensiveObject>::Object& /*object*/)
  {
    // Process the object. (not shown)
  }

  void chap25DemoObjectPool()
  {
    FUNC_INFO;
    ObjectPool<ExpensiveObject> requestPool;

    {
      vector<ObjectPool<ExpensiveObject>::Object> objects;
      for (size_t i = 0; i < 10; ++i) {
        objects.push_back(getExpensiveObject(requestPool));
      }
    }

    cout << "Loop starting." << endl;
    for (size_t i = 0; i < 100; ++i) {
      auto req = getExpensiveObject(requestPool);
      processExpensiveObject(req);
    }
    cout << "Loop finished." << endl;
  }

  void chap25DemoNameDB()
  {
    FUNC_INFO;
    try {
      NameDB boys("boys_long.txt");

      cout << "Daniel rank: " << boys.getNameRank("Daniel") << endl;
      cout << "Jacob rank: " << boys.getNameRank("Jacob") << endl;
      cout << "William rank: " << boys.getNameRank("William") << endl;
    }
    catch (invalid_argument& e)
    {
      cout << "Error " << e.what() << endl;
    }
  }

}
