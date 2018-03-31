#include "StdAfx.h"
#include "Prototype.h"

namespace PrototypePattern {
  //FoodProduct
  FoodProduct::FoodProduct()
  {
    price = 0;
    expireDay = 0;
  }

  FoodProduct::FoodProduct(const std::string& tFoodName, float tFoodPrice, int tExpireDay)
    : expireDay(tExpireDay)
  {
    prouductName = tFoodName;
    price = tFoodPrice;
  }

  FoodProduct::FoodProduct(const FoodProduct &tFoodProduct)
  {
    prouductName = tFoodProduct.prouductName;
    price = tFoodProduct.price;
    expireDay = tFoodProduct.expireDay;
  }

  Product* FoodProduct::clone()
  {
    return new FoodProduct(*this);
  }

  void FoodProduct::ShowMe() {
    cout << "Category: Food" << endl
      << "Name:       " << prouductName << endl
      << "Price:      " << price << endl
      << "ExpireDay:  " << expireDay << endl;

  }

  // BookProduct
  BookProduct::BookProduct() {
    prouductName = "";
    price = 0;
    author = "";
  }

  BookProduct::BookProduct(const std::string& tBookName, float tBookPrice, const string& tAuthor)
  {
    prouductName = tBookName;
    price = tBookPrice;
    author = tAuthor;
  }

  BookProduct::BookProduct(const BookProduct &tBookProduct)
  {
    prouductName = tBookProduct.prouductName;
    price = tBookProduct.price;
    author = tBookProduct.author;
  }

  Product* BookProduct::clone()
  {
    return new BookProduct(*this);
  }

  void BookProduct::ShowMe() {
    cout << "Category: Book" << endl
      << "Name:       " << prouductName << endl
      << "Price:      " << price << endl
      << "Author:  " << author << endl;
  }


  // Prototype Manager
  PrototypeManager::PrototypeManager()
  {
    mapProduct[FOOD] = new FoodProduct("Hot Pot", 3.5, 100);
    mapProduct[BOOK] = new BookProduct("Design Patterns: Elements of Reusable Object- Oriented Software", 20.5, "Erich Gamma");
  }

  PrototypeManager::~PrototypeManager()
  {
    delete mapProduct[FOOD];
    delete mapProduct[BOOK];
  }

  Product* PrototypeManager::CreateProduct(PRODUCT_TYPE en)
  {
    return mapProduct[en]->clone();
  }
  void TestPrototypePattern()
  {
    printf("------------------- in %s -------------------\n", __func__);
    PrototypeManager myProduct;
    auto A = myProduct.CreateProduct(FOOD);
    auto B = myProduct.CreateProduct(BOOK);
    A->ShowMe();
    B->ShowMe();
    delete A;
    delete B;
    A = myProduct.CreateProduct(BOOK);
    A->ShowMe();
    delete A;
  }
}
