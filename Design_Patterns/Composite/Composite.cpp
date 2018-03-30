#include "StdAfx.h"
#include "Composite.h"
#include <iostream>

namespace CompositePattern {

  // Component
  // Class Architecture
  Architecture::~Architecture()
  {
    //delete bName;
  }

  const char* Architecture::GetName()
  {
    return bName;
  }

  void Architecture::ShowMe()
  {
    cout << "Architecture:" << bName << endl;
  }

  Architecture::Architecture(const char *name) : bName(name)
  {}

  void Architecture::setName(const char *name)
  {
    bName = name;
  }

  void Architecture::Add(Architecture *element) 
  {}

  void Architecture::Remove(Architecture *element)
  {}

  list<Architecture*> Architecture::GetChild() 
  { 
    list<Architecture*> tV;  
    return tV; 
  }

  // Leaf
  // Class LeafArchitecture
  LeafArchitecture::~LeafArchitecture()
  {}

  LeafArchitecture::LeafArchitecture(const char *name) : Architecture(name)
  {}

  void LeafArchitecture::ShowMe()
  {
    cout << "LeafArchitecture:" << GetName() << endl;
  }


  // Class Lobby
  Lobby::Lobby(const char *name) :LeafArchitecture(name)
  {}


  Lobby::~Lobby()
  {}

  void Lobby::ShowMe()
  {
    cout << "Lobby:" << GetName() << endl;
  }

  // Class Room
  Room::Room(const char *name) :LeafArchitecture(name)
  {}

  Room::~Room()
  {}

  void Room::ShowMe()
  {
    cout << "Room:" << GetName() << endl;
  }

  // Class Lift
  Lift::Lift(const char *name) : LeafArchitecture(name)
  {}

  Lift::~Lift()
  {}

  void Lift::ShowMe()
  {
    cout << "Lift:" << GetName() << endl;
  }

  // Composite
  // Class CompositeArchitecture
  CompositeArchitecture::~CompositeArchitecture()
  {
    list<Architecture*>::const_iterator it;
    for (it = architectureList.begin(); it != architectureList.end(); it++) {
      (*it)->ShowMe();
      //delete *it;
    }
    architectureList.clear();
  }

  CompositeArchitecture::CompositeArchitecture(const char *name) : Architecture(name)
  {}

  void CompositeArchitecture::ShowMe() const
  {
    list<Architecture*>::const_iterator it;
    for (it = architectureList.begin(); it != architectureList.end(); it++) {
      Architecture& a = **it;
      a.ShowMe();
    }
  }

  void CompositeArchitecture::Add(Architecture *element)
  {
    architectureList.push_back(element);
  }

  void CompositeArchitecture::Remove(Architecture *element)
  {
    architectureList.remove(element);
  }

  list<Architecture*>  CompositeArchitecture::GetChild()
  {
    return architectureList;
  }

  // Class Building
  Building::Building(const char *name) : CompositeArchitecture(name)
  {}

  Building::~Building()
  {}

  void Building::ShowMe()
  {
    cout << "Building:" << GetName() << endl;
    CompositeArchitecture::ShowMe();
  }


  // Class Unit
  Unit::Unit(const char *name) : CompositeArchitecture(name)
  {}

  Unit::~Unit()
  {}

  void Unit::ShowMe()
  {
    cout << "Unit:" << GetName() << endl;
    CompositeArchitecture::ShowMe();
  }

  // Class Level
  Level::Level(const char *name) : CompositeArchitecture(name)
  {}

  Level::~Level()
  {}

  void Level::ShowMe()
  {
    cout << "Level:" << GetName() << endl;
    CompositeArchitecture::ShowMe();
  }

  void TestCompositePattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    Building myBuilding = Building("Graduate Hall");
    Lobby lobby1 = Lobby("Lobby 1");
    Lobby lobby2 = Lobby("Lobby 2");
    Lift lift1 = Lift("Lift 1");
    Lift lift2 = Lift("Lift 2");
    Lift lift3 = Lift("Fireman Lift");
    Unit unit1 = Unit("Unit 1");
    Unit unit2 = Unit("Unit 2");
    Level level1 = Level("Level B2");
    Level level2 = Level("Level B1");
    Level level3 = Level("Level 1");
    Level level4 = Level("Level B2");
    Level level5 = Level("Level B1");
    Level level6 = Level("Level 1");
    Room room1 = Room("Room B2-01");
    Room room2 = Room("Room B2-02");
    Room room3 = Room("Room B2-03");
    Room room4 = Room("Room B2-04");
    Room room5 = Room("Room B1-01");
    Room room6 = Room("Room B1-02");
    Room room7 = Room("Room B1-03");
    Room room8 = Room("Room B1-04");
    myBuilding.Add(&lift3);
    myBuilding.Add(&unit1);
    myBuilding.Add(&unit2);
    unit1.Add(&lift1);
    unit2.Add(&lift2);
    unit1.Add(&level1);
    unit1.Add(&level2);
    unit1.Add(&level3);
    unit2.Add(&level4);
    unit2.Add(&level5);
    unit2.Add(&level6);
    level1.Add(&room1);
    level1.Add(&room2);
    level4.Add(&room3);
    level4.Add(&room4);
    level2.Add(&room5);
    level2.Add(&room6);
    level5.Add(&room7);
    level5.Add(&room8);
    level3.Add(&lobby1);
    level6.Add(&lobby2);
    myBuilding.ShowMe();
  }
}