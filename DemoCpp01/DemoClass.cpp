#include "stdafx.h"
#include "DemoClass.h"

DemoClass::DemoClass(bool fDebug)
{
  printf("fDebug mode: %s\n", fDebug ? "Yes" : "No");
}

DemoClass::~DemoClass()
{
}

DemoChild::DemoChild() :
m_wGridID(0), m_fDebug(false), DemoClass(m_fDebug)
{
  printf("m_wGridID %d\n", m_wGridID);
  printf("m_wLevelID %d\n", m_wLevelID);
  printf("m_wReportID %d\n", m_wReportID);
}

DemoChild::~DemoChild()
{
}
