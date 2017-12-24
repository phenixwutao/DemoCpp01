//  Observer.hpp
#pragma once
#ifndef Observer_hpp
#define Observer_hpp

#include <set>
#include <memory>

class Observer {
public:
    Observer();
    Observer(const Observer &p);
    ~Observer();
    Observer &operator=(const Observer &p); // not implemented

    virtual void notify() = 0;

private:
    
};

class TradeB {};

class TradingLedger;

class TradeObserver : public Observer {
public:
    TradeObserver(TradingLedger *t);
    TradeObserver(const TradeObserver &p);
    ~TradeObserver();
    TradeObserver &operator=(const TradeObserver &p);

    void notify();
    void processNewTrade();
private:
    TradeB m_trade;
    TradingLedger *m_ledger;
};


class TradingLedger {
public:
    TradingLedger();
    TradingLedger(const TradingLedger &p);
    ~TradingLedger();
    TradingLedger &operator=(const TradingLedger &p);

    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    void triggerNotifications();

    void addTrade(const TradeB &t);
    const TradeB &getLastTrade();

private:
    std::set<std::shared_ptr<Observer>> m_observers;
    TradeB m_trade;
};

typedef std::shared_ptr<Observer> PObserver;
typedef std::shared_ptr<TradeObserver> PTradeObserver;

#endif /* Observer_hpp */
