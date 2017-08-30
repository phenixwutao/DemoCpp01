#pragma once

#include <string>
#include <ostream>
#include <istream>

class SpreadsheetCell
{
public:
  // constructors
	SpreadsheetCell();
	SpreadsheetCell(double initialValue);
	explicit SpreadsheetCell(const std::string& initialValue);

  // copy constructor
	SpreadsheetCell(const SpreadsheetCell& src);

  // copy assignment constructor
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

  // interfaces
	void set(double inValue);
	void set(const std::string& inString);

	double getValue() const { mNumAccesses++; return mValue; }
	const std::string& getString() const { mNumAccesses++; return mString; }

	static std::string doubleToString(double inValue);
	static double stringToDouble(const std::string& inString);

	friend SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);

  SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);

	friend bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	friend bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);

	SpreadsheetCell operator-() const;
	SpreadsheetCell& operator++();   // prefix
	SpreadsheetCell operator++(int); // postfix
	SpreadsheetCell& operator--();   // prefix 
	SpreadsheetCell operator--(int); // postfix

  // insertion operator
  friend std::ostream& operator<<(std::ostream& osm, const SpreadsheetCell& cell);
  // extraction operator
  friend std::istream& operator>>(std::istream& ism, SpreadsheetCell& cell);

private:
  double mValue { 0 };
	std::string mString;

	mutable int mNumAccesses = 0;
};
