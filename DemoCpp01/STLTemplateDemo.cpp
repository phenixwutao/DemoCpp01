#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "STLTemplateDemo.h"

using namespace std;

namespace UDemyDemo
{
  void VectorDemo()
  {
    vector<string> strings;

    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");
    
    cout << strings.size() << endl;

    for (size_t i = 0; i<strings.size(); i++) {
      cout << strings[i] << endl;
    }

    for (vector<string>::iterator it = strings.begin(); it != strings.end(); it++) {
      cout << *it << endl;
    }

    vector<string>::iterator it = strings.begin();
    it += 2;

    cout << *it << endl;

    vector<int> idSet;
    idSet.push_back(1);
    idSet.push_back(3);
    idSet.push_back(5);
    for (size_t i = 0; i < idSet.size(); ++i)
      cout << idSet[i] << endl;
    for (vector<int>::iterator it = idSet.begin(); it != idSet.end(); ++it)
      cout << *it << endl;
    auto it2 = idSet.begin();
    cout << *(it2 + 1) << endl;
  }

  void VectorCapacity()
  {
    vector<double> numbers(0);

    cout << "Size: " << numbers.size() << endl;

    int capacity = numbers.capacity();
    cout << "Capacity: " << capacity << endl;

    for (int i = 0; i<10000; i++) {

      if (numbers.capacity() != capacity) {
        capacity = numbers.capacity();
        cout << "Capacity: " << capacity << endl;
      }

      numbers.push_back(i);
    }

    //numbers.clear(); // clear elements doesn't change capacity
    cout << "clear Capacity: " << numbers.capacity() << endl;
    numbers.resize(3);
    cout << "resize Capacity: " << numbers.capacity() << endl;
    //numbers.reserve(100000);
    numbers.reserve(100);
    cout << numbers[2] << endl;
    cout << "Size: " << numbers.size() << endl;
    cout << "Capacity: " << numbers.capacity() << endl;
    numbers.shrink_to_fit();
    cout << "shrink_to_fit Size: " << numbers.size() << endl;
    cout << "shrink_to_fit Capacity: " << numbers.capacity() << endl;

    numbers.clear();
    cout << "Size: " << numbers.size() << endl;
    cout << "Capacity: " << numbers.capacity() << endl;
  }

  //print 12 time table
  void Vector2Dim(const size_t wLimit)
  {
    vector<vector<int>> timeTable;
    vector<vector<int>> timeTableValue;
    for (size_t row = 1; row <= wLimit; ++row)
    {
      vector<int> RowTable;
      vector<int> RowTableValue;
      for (size_t col = 1; col <= row; ++col)
      {
        RowTable.push_back(col);
        RowTableValue.push_back(row*col);
      }
      timeTable.push_back(RowTable);
      timeTableValue.push_back(RowTableValue);
    }

    // print time table
    for (size_t row = 0; row < timeTable.size(); ++row)
    {
      for (size_t col = 0; col < timeTable[row].size(); ++col)
      {
        cout << timeTable[row][col] << " "<< flush;
      }
      cout << endl;
    }

    // print time table values
    for (size_t row = 0; row < timeTableValue.size(); ++row)
    {
      for (size_t col = 0; col < timeTableValue[row].size(); ++col)
      {
        cout << (row+1)<<"x"<<(col+1) << "=" << timeTableValue[row][col] << " " << flush;
      }
      cout << endl;
    }

    cout << endl;
  }

  void ListDemo()
  {
    list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(5);
    numbers.push_back(9);
    numbers.push_front(11);
    numbers.push_front(13);
    for (const auto it : numbers)
      cout << it << endl;


    for (auto it = numbers.begin(); it != numbers.end(); ++it)
      cout << *it << endl;

    list<int>::iterator it2 = numbers.begin();
    while(it2 != numbers.end())
    {
      if (*it2 == 11)
        it2 = numbers.erase(it2);  // get iterator after erase
      else
        ++it2; // self-increment
    }
    cout << "after erase" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
      cout << *it << endl;
  }

  void MapDemo()
  {
    map<string, int> ages;
    ages["Mike"] = 40;
    ages["Adam"] = 20;
    ages["Sue"] = 30;
    ages.insert(make_pair("Daniel", 35));
    ages.insert(pair<string, int>("Rachel", 26));
    ages.emplace(make_pair("Rose", 100));

    for (map<string, int>::const_iterator it = ages.cbegin(); it != ages.cend(); ++it)
    {
      cout << it->first << ": " << it->second << endl;
    }

    string name = "Rose2";
    if (ages.find(name) != ages.end())
    {
      cout << "find " << name << " with age:" << ages[name] << endl;
    }
    else
      cout << "key " << name << " not found"<< endl;

  }

}
