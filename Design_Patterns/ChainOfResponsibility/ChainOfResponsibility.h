#pragma once
namespace ChainOfResponsibility
{
  // Here simplify the composite pattern to one concrete component
  class KongfuMan {
  public:
    ~KongfuMan();
    KongfuMan(const char* name, int tlevel);
    void ChangeMaster(KongfuMan* tmaster);

    // Composite parts
    void Add(KongfuMan* prentice);
    void Remove(KongfuMan* prentice);

    // Responsibility (Handle request)
    void FaceChallenge(int clevel);

  private:
    void ShowMe();
    const char* myName;
    int level = -1;
    KongfuMan* master = nullptr; // The master of this KongfuMan  .. as successor
  };

  void TestChainOfResponsibility();
}