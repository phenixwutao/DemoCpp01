//
//  Observer.cpp
#include "StdAfx.h"
#include "Chap05Observer.h"

//using std::shared_ptr;
//typedef shared_ptr<Observer> PObserver;
//typedef shared_ptr<TradeObserver> PTradeObserver;

Observer::Observer()
{
}

Observer::Observer(const Observer &p)
{
}

Observer::~Observer()
{
}

void Observer::notify()
{
}

TradeObserver::TradeObserver(TradingLedger *t)
: m_ledger(t)
{
}

TradeObserver::TradeObserver(const TradeObserver &p)
: m_trade(p.m_trade),
  m_ledger(p.m_ledger)
{
}

TradeObserver::~TradeObserver()
{
}

TradeObserver &TradeObserver::operator=(const TradeObserver &p)
{
    if (this != &p)
    {
        m_trade = p.m_trade;
        m_ledger = p.m_ledger;
    }
    return *this;
}

void TradeObserver::notify()
{
    this->processNewTrade();
}

void TradeObserver::processNewTrade()
{
    m_trade = m_ledger->getLastTrade();
    // do trading processing here
}


//

TradingLedger::TradingLedger()
{
}

TradingLedger::TradingLedger(const TradingLedger &p)
: m_observers(p.m_observers),
  m_trade(p.m_trade)
{
}

TradingLedger::~TradingLedger()
{
}

TradingLedger &TradingLedger::operator=(const TradingLedger &p)
{
    if (this != &p)
    {
        m_observers = p.m_observers;
        m_trade = p.m_trade;
    }
    return *this;
}

void TradingLedger::addObserver(std::shared_ptr<Observer> observer)
{
    m_observers.insert(observer);
}

void TradingLedger::removeObserver(std::shared_ptr<Observer> observer)
{
    if (m_observers.find(observer) != m_observers.end())
    {
        m_observers.erase(observer);
    }
}

void TradingLedger::triggerNotifications()
{
    for (auto i : m_observers)
    {
        i->notify();
    }
}

void TradingLedger::addTrade(const TradeB &t)
{
    m_trade = t;
    this->triggerNotifications();
}

const TradeB &TradingLedger::getLastTrade()
{
    return m_trade;
}
