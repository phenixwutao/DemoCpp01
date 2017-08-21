#pragma once
#include <string>
using std::string;

class Muffin
{
public:
  const string& getDescription() const;
  void setDescription(const string& inDesc);
  int getSize() const;
  void setSize(int inSize);
  bool getHasChocolateChips() const;
  void setHasChocolateChips(bool inChips);
  void output();

private:
  string mDesc;
  int mSize;
  bool mHasChocolateChips;
};
