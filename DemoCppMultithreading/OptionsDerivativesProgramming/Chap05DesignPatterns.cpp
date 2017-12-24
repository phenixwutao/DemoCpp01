//
//  DesignPatterns.cpp
#include "StdAfx.h"
#include "Chap05DesignPatterns.h"
#include <iostream>

ClearingHouse *ClearingHouse::s_clearingHouse = nullptr;


ClearingHouse::ClearingHouse()
{
  printf("ClearingHouse constructor\n");
}

ClearingHouse::~ClearingHouse()
{
  printf("ClearingHouse destructor\n");
}

ClearingHouse &ClearingHouse::getClearingHouse()
{
    if (!s_clearingHouse)
    {
        s_clearingHouse = new ClearingHouse();
    }
    return *s_clearingHouse;
}

void ClearingHouse::DestroyClearingHouse(ClearingHouse* p)
{
  if (s_clearingHouse != nullptr)
    delete s_clearingHouse;
}


void ClearingHouse::clearTrade(const Trade &t)
{
}
