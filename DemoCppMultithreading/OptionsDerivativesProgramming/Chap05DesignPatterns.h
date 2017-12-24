//
//  DesignPatterns.hpp CppOptions
#pragma once

#ifndef DESIGNPATTERNS_HPP
#define DESIGNPATTERNS_HPP

class Trade {
    //  ....
};

class ClearingHouse {
private:                   // these are all private because this is a singleton
    ClearingHouse();
    // the copy constructor is not implemented
    ClearingHouse(const ClearingHouse &p);
    ~ClearingHouse();
    // assignment operator is not implemented
    ClearingHouse &operator=(const ClearingHouse &p);

public:
    static ClearingHouse &getClearingHouse();
    static void DestroyClearingHouse(ClearingHouse* p);

    void clearTrade(const Trade &);

private:
    static ClearingHouse *s_clearingHouse;
};
#endif /* DesignPatterns_hpp */
