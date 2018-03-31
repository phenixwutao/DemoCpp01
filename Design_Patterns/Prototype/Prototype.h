#pragma once
#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace PrototypePattern {
  // Product type enum
  enum PRODUCT_TYPE {
    FOOD,
    BOOK
  };

  // Abstract Products class
  class Product {
  public:
    virtual Product* clone() = 0;
    virtual void ShowMe() = 0;
    virtual ~Product() {}

  protected:
    string prouductName;
    float price;
  };


  // Concrete Products class
  class FoodProduct : public Product {
  public:
    FoodProduct();
    FoodProduct(const string& tFoodName, float tFoodPrice, int tExpireDay);
    FoodProduct(const FoodProduct& tFoodProduct);
    virtual ~FoodProduct() {}
    virtual Product* clone();
    virtual void ShowMe();
  protected:
    int expireDay;
  };

  class BookProduct : public Product {
  public:
    BookProduct();
    BookProduct(const string& tBookName, float tBookPrice, const string& tAuthor);
    BookProduct(const BookProduct& tBookProduct);
    virtual ~BookProduct() {}
    virtual Product* clone();
    virtual void ShowMe();
  protected:
    string author;
  };

  // Prototype Manager
  class PrototypeManager {
  public:
    PrototypeManager();
    ~PrototypeManager();
    Product* CreateProduct(PRODUCT_TYPE en);
  private:
    map<PRODUCT_TYPE, Product*> mapProduct;
  };
  void TestPrototypePattern();
}