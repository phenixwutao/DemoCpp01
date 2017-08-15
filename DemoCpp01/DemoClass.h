#pragma once
class DemoClass
{
public:
  DemoClass(bool fDebug);
  virtual ~DemoClass();

};

class DemoChild : public DemoClass
{
public:
  DemoChild();
  virtual ~DemoChild();

private:
  int m_wGridID{ 1 };
  int m_wLevelID{ 2 };
  int m_wReportID{ 3 };
  bool m_fDebug{ false };
};