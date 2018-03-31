#include "StdAfx.h"
#include "Iterator.h"

namespace IteratorPattern
{
  // Class Recipe
  Recipe::~Recipe() {

  }

  Recipe::Recipe(const char* tName) : name(tName) {

  }

  void Recipe::Print() {
    cout << name << endl;
  }

  void TestIteratorPattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    Recipe myRecipe1("Fish Filets in Hot Chili Oil");
    Recipe myRecipe2("Boiled Fish with Pickled Cabbage and Chili ");
    Recipe myRecipe3("Coke Chicken");
    Recipe myRecipe4("Fish ball soup");
    List<Recipe>* myRecipeList = new List<Recipe>();
    myRecipeList->Append(myRecipe1);
    myRecipeList->Append(myRecipe2);
    myRecipeList->Append(myRecipe3);
    myRecipeList->Append(myRecipe4);
    ListIterator<Recipe> myIterator(myRecipeList);
    for (myIterator.First(); !myIterator.IsDone(); myIterator.Next())
    {
      myIterator.CurrentItem().Print();
    }
  }
}
