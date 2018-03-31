#pragma once

#include <iostream>
#include <string>
using namespace std;
namespace MediatorPattern {
  // Forward declaration 
  class FamilyDirector;

  class FamilyMember {
  public:
    FamilyMember(FamilyDirector* tDirector);
    ~FamilyMember();
    void SendRequest();
    void SetRequest(const std::string& tRequest);
    const std::string& GetRequest();
  protected:
    FamilyDirector * myDirector = nullptr;
    std::string myRequest;
  };

  class Mother : public FamilyMember {
  public:
    Mother(FamilyDirector* tDirector);
    void Cook();
    void Clean();
    void Wash();
  };

  class Father : public FamilyMember {
  public:
    Father(FamilyDirector* tDirector);
    void Teach();
    void Work();
  };

  class Child : public FamilyMember {
  public:
    Child(FamilyDirector* tDirector);
    void Study();
    void Shower();
    void Sleep();
  };

  class Grandma : public FamilyMember {
  public:
    Grandma(FamilyDirector* tDirector);
    void lull();
  };

  class FamilyDirector {
  public:
    FamilyDirector();
    virtual ~FamilyDirector();
    virtual void HandleEvent(FamilyMember* sender);
    Mother*   GetMother();
    Father*   GetFather();
    Child*    GetChild();
    Grandma*  GetGrandma();
  private:
    Mother*   myMother;
    Father*   myFather;
    Child*    myChild;
    Grandma*  myGrandma;
  };
  void TestMediatorPattern();
}
