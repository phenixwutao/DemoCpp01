#pragma once

#include <iostream>
using namespace std;
namespace StatePattern {
  class Mood;

  class Dad {
  public:
    Dad(const char* name);
    ~Dad();
    void LoseMoney();
    void BlazedByMother();
    void DisturbedByChild();
    void NiceDiner();
    const char* GetName();
  private:
    friend class Mood;
    void ChangeMood(Mood* newMood);
  private:
    Mood * myMood;
    const char* myName;
  };

  class Mood {
  public:
    virtual ~Mood();
    virtual void LoseMoney(Dad* tDadPara);
    virtual void BlazeByMother(Dad* tDadPara);
    virtual void DisturbedByChild(Dad* tDadPara);
    virtual void NiceDinner(Dad* tDadPara);
  protected:
    Mood();
  protected:
    virtual void ChangeMood(Dad* tDadPara, Mood* newMood);
  };

  class Happy : public Mood {
  public:
    Happy();
    virtual ~Happy();
    virtual void LoseMoney(Dad* tDadPara) override;
    virtual void BlazeByMother(Dad* tDadPara) override;
    virtual void DisturbedByChild(Dad* tDadPara) override;
    virtual void NiceDinner(Dad* tDadPara) override;
  };

  class Common : public Mood {
  public:
    Common();
    virtual ~Common();
    virtual void LoseMoney(Dad* tDadPara) override;
    virtual void BlazeByMother(Dad* tDadPara) override;
    virtual void DisturbedByChild(Dad* tDadPara) override;
    virtual void NiceDinner(Dad* tDadPara) override;
  };

  class Angry : public Mood {
  public:
    Angry();
    virtual ~Angry();
    virtual void LoseMoney(Dad* tDadPara) override;
    virtual void BlazeByMother(Dad* tDadPara) override;
    virtual void DisturbedByChild(Dad* tDadPara) override;
    virtual void NiceDinner(Dad* tDadPara) override;
  };
  void TestStatePattern();
}