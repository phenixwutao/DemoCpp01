#pragma once

namespace AdapterObject {
  // Old version interface
  class OldVersion
  {
  public:
    OldVersion();
    void OldDisplay(int input);
  };


  // New version interface
  class NewVersion
  {
  public:
    NewVersion(int input);
    virtual void Display();
  protected:
    int myData;
  };

  // Adapter
  class Adapter : public NewVersion
  {
  public:
    Adapter(int input);
    void Display();
    ~Adapter();
  private:
    OldVersion * oldVersion;
  };

  void TestAdapterObject();
}