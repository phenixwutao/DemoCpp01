#include "stdafx.h"
#include "ProfCpp4thCh10.h"
#include "SpreadsheetCell10.h"
#include "DoubleSpreadsheetCell10.h"
#include "StringSpreadsheetCell10.h"

#include "BingCherryTree.h"

#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
using namespace std;

namespace chap10
{
  namespace DemoOverload
  {
    class Base
    {
    public:
      virtual ~Base() = default;
      virtual void info()
      {
        printf("Base info\n");
      }

      void Run() {
        printf("Base run\n");
      }
      virtual void calc() final {}
    };

    class Sub : public Base
    {
    public:
      virtual ~Sub() = default;

      void info() override
      {
        printf("Sub info\n");
      }
      
      // void calc() override {} // cannot override this function

      void Run() {
        printf("Sub run\n");
      }
    };
  }

  void chap10DemoClassMethodOverload()
  {
    FUNC_INFO;
    DemoOverload::Base b;
    b.Run();
    DemoOverload::Sub s;
    s.Run();

    DemoOverload::Base& refb = b;
    refb.Run();

    DemoOverload::Base& refs = s;
    refs.Run();

    DemoOverload::Base* pb = new DemoOverload::Base;
    pb->Run();
    delete pb;

    DemoOverload::Base* ps = new DemoOverload::Sub;
    ps->Run();
    delete ps;
  }

  void chap10DemoClassMethodOverride()
  {
    FUNC_INFO;
    DemoOverload::Base b;
    b.info();
    DemoOverload::Sub s;
    s.info();

    DemoOverload::Base& refb = b;
    refb.info();

    DemoOverload::Base& refs = s;
    refs.info();

    DemoOverload::Base* pb = new DemoOverload::Base;
    pb->info();
    delete pb;

    DemoOverload::Base* ps = new DemoOverload::Sub;
    ps->info();
    delete ps;
  }

  namespace VirtualMethod
  {
    class Base {
    public:
      Base()
      {
        info();
      }
      virtual ~Base() = default;
      virtual void info() {  printf("Base info\n");  }
    };

    class Sub : public Base {
    public:
      Sub()
      {
        info();
      }
      virtual ~Sub() = default;
      virtual void info() { printf("Sub info\n"); }
    };

    class Object
    {
    public:
      Object() { cout << "2\n"; }
      virtual ~Object() { cout << "2\n"; }
    };

    class Parent
    {
    public:
      Parent() { cout << "1\n"; }
      virtual ~Parent() { cout << "1\n"; info(); }
      virtual void info() { cout << "Parent info" << endl; }
    };

    class Child : public Parent
    {
    public:
      Child() { cout << "3\n"; }
      virtual ~Child() { cout << "3\n"; info(); }
      virtual void info()
      {
        // Microsoft Visual C++ supports the __super keyword
        __super::info();

        cout << "Child info" << endl;
      }

    private:
      Object mObj;
    };
  }
  void chap10DemoConstructorCallVirtualMethod()
  {
    FUNC_INFO;
    VirtualMethod::Base* p = new VirtualMethod::Sub;
    delete p;

    VirtualMethod::Parent* pParent = new VirtualMethod::Child;
    delete pParent;
  }

  namespace PolymorphicSpreadsheet
  {
    StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs,
                                    const StringSpreadsheetCell& rhs)
    {
      StringSpreadsheetCell newCell;
      newCell.set(lhs.getString() + rhs.getString());
      return newCell;
    }
  }

  void chap10DemoPolymorphicSpreadsheet()
  {
    FUNC_INFO;
    vector<unique_ptr<SpreadsheetCell>> cellArray;

    cellArray.push_back(make_unique<StringSpreadsheetCell>());
    cellArray.push_back(make_unique<StringSpreadsheetCell>());
    cellArray.push_back(make_unique<DoubleSpreadsheetCell>());

    cellArray[0]->set("hello");
    cellArray[1]->set("10");
    cellArray[2]->set("18");

    cout << "Vector values are [" << 
      cellArray[0]->getString() << "," <<
      cellArray[1]->getString() << "," <<
      cellArray[2]->getString() << "]" << endl;

    DoubleSpreadsheetCell myDbl;
    myDbl.set(8.4);

    using namespace PolymorphicSpreadsheet;
    // call copy constructor from DoubleSpreadsheetCell, then call operator+
    StringSpreadsheetCell result = myDbl + myDbl;
    cout << endl << result.getString() << endl;

    // explicitly call PolymorphicSpreadsheet::operator+
    auto result2 = PolymorphicSpreadsheet::operator+(myDbl, myDbl);
    cout << result2.getString() << endl;
  }

  namespace MultiInheritance {

    class Dog
    {
    public:
      virtual void bark() { cout << "woof!" << endl; }
      virtual void eat() { cout << "The dog ate." << endl; }
    };

    class Bird
    {
    public:
      virtual void chirp() { cout << "chirp!" << endl; }
      virtual void eat() { cout << "The bird ate." << endl; }
    };

    class DogBird : public Dog, public Bird
    {
    public:
      // void eat() override; // compiler error
      using Dog::eat;       // Explicitly inherit Dog's version of eat()
    };

    //void DogBird::eat()
    //{
    //	Dog::eat();  // Explicitly call Dog's version of eat()
    //}
  }

  void chap10DemoMultiInheritance()
  {
    FUNC_INFO;
    using namespace MultiInheritance;
    DogBird myConfusedAnimal;

    myConfusedAnimal.bark();
    myConfusedAnimal.chirp();
    myConfusedAnimal.eat();                   // Error! Ambiguous call to method eat()
    dynamic_cast<Dog&>(myConfusedAnimal).eat(); // Calls Dog::eat()
    myConfusedAnimal.Dog::eat();                // Calls Dog::eat()
  }

  namespace Diamond {
    class Animal
    {
    public:
      virtual void eat() = 0;
    };

    class Dog : public Animal
    {
    public:
      virtual void bark() { cout << "woof!" << endl; }
      virtual void eat() override { cout << "The dog ate." << endl; }
    };

    class Bird : public Animal
    {
    public:
      virtual void chirp() { cout << "chirp!" << endl; }
      virtual void eat() override { cout << "The bird ate." << endl; }
    };

    class DogBird : public Dog, public Bird
    {
    public:
      using Dog::eat;
    };
  }

  void chap10DemoDiamondClass()
  {
    FUNC_INFO;
    Diamond::DogBird myConfusedAnimal;
    myConfusedAnimal.eat();
  }

  void chap10DemoPickCherry()
  {
    FUNC_INFO;
    using namespace Chap10;
    BingCherryTree theTree;
    std::unique_ptr<Cherry> theCherry(theTree.pick());
    theCherry->printType();
  }

  namespace InheritCtor
  {
    class Base
    {
    public:
      virtual ~Base() = default;
      Base() = default;
      Base(std::string_view str) {}
    };

    class Derived : public Base
    {
    public:
      // The using statement inherits all constructors from the parent class
      // except the default constructor
      using Base::Base;

      Derived(int i) {}
    };
  }
  void chap10DemoInheritedConstructor()
  {
    FUNC_INFO;
    InheritCtor::Base base("Hello");        // OK, calls string_view Base ctor
    InheritCtor::Derived derived1(1);       // OK, calls integer Derived ctor
    InheritCtor::Derived derived2("Hello"); // Error, Derived does not inherit string_view ctor
  }

  namespace StaticMethod
  {
    class BaseStatic
    {
    public:
      static void beStatic()
      {
        cout << "BaseStatic static." << endl;
      }
    };

    class DerivedStatic : public BaseStatic
    {
    public:
      static void beStatic()
      {
        cout << "DerivedStatic static." << endl;
      }
    };
  }

  /**********************************************************************************
  * static methods are scoped by the name of the class in which they are defined,
  * but they are not methods that apply to a specific object. When you call a static
  * method, the version determined by normal name resolution is called. When the
  * method is called syntactically by using an object, the object is not actually
  * involved in the call, except to determine the type at compile time.
  ***********************************************************************************/
  void chap10DemoOverrideStaticMethod()
  {
    FUNC_INFO;
    StaticMethod::DerivedStatic myDerivedStatic;
    StaticMethod::BaseStatic& ref = myDerivedStatic;
    myDerivedStatic.beStatic();
    ref.beStatic(); // static method is compile-time type, not run-time
  }

  namespace MyOverload
  {
    class Base
    {
    public:
      virtual ~Base() = default;
      virtual void overload() { cout << "Base's overload()" << endl; }
      virtual void overload(int i)
      {
        cout << "Base's overload(int i)" << endl;
      }
    };

    class Derived : public Base
    {
    public:
      virtual void overload() override
      {
        cout << "Derived's overload()" << endl;
      }
    };
  }
  void chap10DemoBaseClassMethodOverload()
  {
    FUNC_INFO;
    MyOverload::Derived myDerived;
    // myDerived.overload(2); // Error! No matching method for overload(int)
    myDerived.Base::overload(2); // ok
    MyOverload::Base& b = myDerived;
    b.overload(3); // call Base class overload(int i), since derived class doesn't override it
  }

  namespace DefaultArgument {
    class A {
    public:
      virtual ~A() = default;
      virtual void go(int i = 1) { cout << "A::go Base " << i << endl; }
    };
    class B : public A {
    public:
      virtual ~B() = default;
      virtual void go(int i = 2) override { cout << "B::go Deriv " << i << endl; }
    };
  }
  void chap10DemoBaseClassMethodHasDefaultArguments()
  {
    FUNC_INFO;
    DefaultArgument::A myBase;
    DefaultArgument::B myDeriv;
    DefaultArgument::A& myBaseReferenceToDerived = myDeriv;
    myBase.go();
    myDeriv.go();
    /*
    * uses the compile-time type of the expression to bind default arguments, 
    * not the run-time type. Default arguments are not "inherited" in C++. 
    * If the Derived class in this example failed to provide a default argument
    * as its parent did, it would be overloading the go() method with a new 
    * non-zero-argument version.
    */
    myBaseReferenceToDerived.go();
  }

  namespace AccessLevel {
    class A {
    public:
      virtual ~A() = default;
      virtual void calc() { cout << "A::calc base " << endl; }
    protected:
      virtual void dontTell() { cout << "I'll never tell." << endl; }
    };
    class B : public A {
    public:
      virtual ~B() = default;
      using A::dontTell;

    private:
      virtual void calc() override { cout << "B::calc deriv" << endl; }
    };
  }
  void chap10DemoClassMethodHasDifferentAccessLevel()
  {
    FUNC_INFO;
    AccessLevel::A myBase;
    AccessLevel::B myDeriv;
    myBase.calc();
    // myDeriv.go(); // error method is inaccessible

    AccessLevel::A& myBaseRef = myDeriv;
    myBaseRef.calc(); // OK

    AccessLevel::B b2;
    AccessLevel::A& ref = b2;
    AccessLevel::A* ptr = &b2;
    // ref.dontTell();  // function is inaccessbile
    // ptr->dontTell(); // function is inaccessbile
    b2.dontTell(); // OK
  }

  namespace DemoDerivCopy {
    class Base
    {
    public:
      virtual ~Base() = default;
      Base() { printf("Base default ctor\n"); }
      Base(const Base& src) { printf("Base copy ctor\n"); }
      Base& operator=(const Base& src)
      {
        printf("Base copy assignment ctor\n");
        return *this;
      }
    };
    class Derived : public Base
    {
    public:
      Derived() = default;

      /********************************************************************************
      * If your derived class does not specify its own copy constructor or operator=, 
      * the base class functionality continues to work. However, if the derived class 
      * does provide its own copy constructor or operator=, it needs to explicitly 
      * call the base class versions
      ********************************************************************************/
      Derived(const Derived& src) : Base(src)
      {
        printf("Derived copy ctor\n");
      }
      Derived& operator=(const Derived& src)
      {
        Base::operator=(src); // call base operator=
        printf("Derived copy assignment ctor\n");
        return *this;
      }
    };
  }
  void chap10DemoCopyConstructorsDerivedClass()
  {
    FUNC_INFO;
    DemoDerivCopy::Derived d1;
    DemoDerivCopy::Derived d2 = d1;
    d2 = d1;
  }

  namespace RTTI {
    class Animal { public: virtual ~Animal() = default; };
    class Dog : public Animal {};
    class Bird : public Animal {};

    void speak(const Animal& animal)
    {
      if (typeid(animal) == typeid(Dog))
      {
        cout << "Woof!" << endl;
      }
      else if (typeid(animal) == typeid(Bird))
      {
        cout << "Chirp!" << endl;
      }
      else if (typeid(animal) == typeid(Animal))
      {
        cout << "Animal!" << endl;
      }
    }
  }
  void chap10DemoRunTimeTypeInformation()
  {
    FUNC_INFO;
    RTTI::Animal animal;
    RTTI::Dog dog;
    RTTI::Bird bird;
    RTTI::speak(animal);
    RTTI::speak(dog);
    RTTI::speak(bird);
  }

  namespace Logging
  {
    class Loggable
    {
    public:
      virtual ~Loggable() = default;
      virtual std::string getLogMessage() const = 0;
    };
    class Foo : public Loggable
    {
    public:
      std::string getLogMessage() const override;
    };

    std::string Foo::getLogMessage() const
    {
      return "Hello logger.";
    }

    void logObject(const Loggable& loggableObject)
    {
      cout << "Name is: " << typeid(loggableObject).name() << ": ";
      cout << loggableObject.getLogMessage() << endl;
    }

  }
  void chap10DemoTypeidLogging()
  {
    FUNC_INFO;
    Logging::Foo foo;
    Logging::logObject(foo);
  }
}