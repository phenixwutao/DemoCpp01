#include "StdAfx.h"

#include "FileError.h"

FileOpenError::FileOpenError(const string& fileNameIn) : FileError(fileNameIn)
{
  setMessage("Unable to open " + fileNameIn);
}

FileReadError::FileReadError(const string& fileNameIn, int lineNumIn) :
  FileError(fileNameIn), mLineNum(lineNumIn)
{
  ostringstream ostr;

  ostr << "Error reading " << fileNameIn << " at line " << lineNumIn;
  setMessage(ostr.str());
}
