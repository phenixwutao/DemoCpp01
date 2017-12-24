//
//  DataSource.cpp
#include "StdAfx.h"
#include "Chap05DataSource.h"


DataSource::DataSource(const std::string &name)
: m_dataName(name)
{
}

DataSource::DataSource(const DataSource &p)
: m_dataName(p.m_dataName)
{
}

DataSource &DataSource::operator=(const DataSource &p)
{
    if (this != &p)
    {
        m_dataName = p.m_dataName;
    }
    return *this;
}

DataSource::~DataSource()
{
}


DataSource *DataSource::createInstance()
{
    std::string sourceName;
    // complex method used here to find sourceName and other construction parameters ....
    DataSource *ds = new DataSource(sourceName);
    return ds;
}

void DataSource::readData()
{
    // read data here ...
}

