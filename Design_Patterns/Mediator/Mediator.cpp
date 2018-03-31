#include "StdAfx.h"
#include "Mediator.h"
namespace MediatorPattern
{
  // Class FamilyDirector
  FamilyDirector::FamilyDirector()
  {
    myMother  = new Mother(this);
    myFather  = new Father(this);
    myChild   = new Child(this);
    myGrandma = new Grandma(this);
  }

  FamilyDirector::~FamilyDirector()
  {
    delete myMother;
    delete myFather;
    delete myChild;
    delete myGrandma;
  }

  void FamilyDirector::HandleEvent(FamilyMember* sender)
  {
    auto sRequest = sender->GetRequest();
    if ("Wash Cloth!" == sRequest)
    {
      myMother->Wash();
    }
    else if ("Clean Room!" == sRequest)
    {
      myMother->Clean();
    }
    else if ("Cook Dinner!" == sRequest)
    {
      myMother->Cook();
    }
    else if ((sender == myChild) && (sRequest == "I want to sleep!"))
    {
      myGrandma->lull();
      myChild->Sleep();
    }
    else if ((sender == myChild) && (sRequest == "I want to study!"))
    {
      myFather->Teach();
      myChild->Study();
    }
    else if ((sender == myMother) && (sRequest == "Shower!"))
    {
      myChild->Shower();
    }
    else if ((sender == myMother) && (sRequest == "Work!"))
    {
      myFather->Work();
    }
  }

  Mother* FamilyDirector::GetMother()
  {
    return myMother;
  }

  Father* FamilyDirector::GetFather()
  {
    return myFather;
  }

  Child* FamilyDirector::GetChild()
  {
    return myChild;
  }

  Grandma* FamilyDirector::GetGrandma()
  {
    return myGrandma;
  }

  // Class FamilyMember
  FamilyMember::FamilyMember(FamilyDirector* tDirector) :
    myDirector(tDirector)
  {
  }

  FamilyMember::~FamilyMember()
  {
    //delete myDirector;
  }

  void FamilyMember::SendRequest()
  {
    myDirector->HandleEvent(this);
  }

  void FamilyMember::SetRequest(const std::string& tRequest)
  {
    myRequest = tRequest;
  }

  const std::string& FamilyMember::GetRequest()
  {
    return myRequest;
  }

  // Class Mother
  Mother::Mother(FamilyDirector* tDirector) : FamilyMember(tDirector)
  {
  }

  void Mother::Cook()
  {
    cout << "Mom is cooking!" << endl;
  }

  void Mother::Clean()
  {
    cout << "Mom is cleaning the rooms!" << endl;
  }

  void Mother::Wash()
  {
    cout << "Mom is washing cloth!" << endl;
  }


  // Class father
  Father::Father(FamilyDirector* tDirector) : FamilyMember(tDirector)
  {
  }

  void Father::Teach()
  {
    cout << "Dad is teach little baby!" << endl;
  }

  void Father::Work()
  {
    cout << "Dad is working!" << endl;
  }

  // Class Child
  Child::Child(FamilyDirector* tDirector) : FamilyMember(tDirector)
  {
  }

  void Child::Study()
  {
    cout << "The baby is studying!" << endl;
  }

  void Child::Shower()
  {
    cout << "The baby is showering!" << endl;
  }

  void Child::Sleep()
  {
    cout << "The baby is sleeping!" << endl;
  }

  // Class Grandma
  Grandma::Grandma(FamilyDirector* tDirector) : FamilyMember(tDirector)
  {
  }

  void Grandma::lull()
  {
    cout << "The grandma is singing the baby to sleep!" << endl;
  }

  void TestMediatorPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    FamilyDirector myDirector;
    myDirector.GetChild()->SetRequest("I want to sleep!");
    myDirector.GetChild()->SendRequest();
    myDirector.GetFather()->SetRequest("Clean Room!");
    myDirector.GetFather()->SendRequest();
    myDirector.GetMother()->SetRequest("Shower!");
    myDirector.GetMother()->SendRequest();
  }
}