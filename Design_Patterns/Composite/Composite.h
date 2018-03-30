#pragma once

#include <list>
using namespace std;

namespace CompositePattern {

  // Component
  class Architecture
  {
  public:
    virtual ~Architecture();
    virtual void ShowMe();

    virtual void Remove(Architecture* element);
    virtual void Add(Architecture* element);
    virtual list<Architecture*> GetChild();

  protected:
    Architecture(const char* name);
    const char* GetName();
    void setName(const char *name);

  private:
    const char* bName;
  };

  // Leaf
  class LeafArchitecture : public Architecture
  {
  public:
    virtual ~LeafArchitecture();
    virtual void ShowMe();
  protected:
    LeafArchitecture(const char* name);
  };

  class Lobby : public LeafArchitecture
  {
  public:
    Lobby(const char* name);
    virtual ~Lobby();
    virtual void ShowMe();
  };

  class Room : public LeafArchitecture
  {
  public:
    Room(const char* name);
    virtual ~Room();
    virtual void ShowMe();
  };

  class Lift : public LeafArchitecture
  {
  public:
    Lift(const char* name);
    virtual ~Lift();
    virtual void ShowMe();
  };

  // Composite
  class CompositeArchitecture : public Architecture
  {
  public:
    virtual ~CompositeArchitecture();
    virtual void ShowMe() const;

    virtual void Remove(Architecture* element);
    virtual void Add(Architecture* element);
    virtual list<Architecture*> GetChild();

  protected:
    CompositeArchitecture(const char* name);

  protected:
    list<Architecture*> architectureList;

  };

  class Building : public CompositeArchitecture
  {
  public:
    Building(const char* name);
    virtual ~Building();
    virtual void ShowMe();
  };

  class Unit : public CompositeArchitecture {
  public:
    Unit(const char* name);
    virtual ~Unit();
    virtual void ShowMe();
  };

  class Level : public CompositeArchitecture {
  public:
    Level(const char* name);
    virtual ~Level();
    virtual void ShowMe();
  };
  void TestCompositePattern();
}