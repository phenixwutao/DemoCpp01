#pragma once

#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

// FileError extand from exception class
class FileError : public exception
{
public:
  FileError(const string& fileIn) : mFile(fileIn) {}
  virtual const char* what() const noexcept override { return mMsg.c_str(); }
  const string& getFileName() { return mFile; }

protected:
  void setMessage(const string& message) { mMsg = message; }

private:
  string mFile, mMsg;
};

class FileOpenError : public FileError
{
public:
  FileOpenError(const string& fileNameIn);
};

class FileReadError : public FileError
{
public:
  FileReadError(const string& fileNameIn, int lineNumIn);
  int getLineNum() { return mLineNum; }

private:
  int mLineNum;
};
