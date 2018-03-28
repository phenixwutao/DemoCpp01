#pragma once

// Old version interface
class OldVersion
{
public:
	OldVersion();
	void OldDisplay(int input);
};


// New version interface    // can be abstract
class NewVersion
{
public:
	NewVersion(int input);
	virtual void Display();  // Can be abstract

protected:
	int myData;
};

// Adapter
class Adapter: public NewVersion, private OldVersion
{
public:
	Adapter(int input);
	void Display();   // implement with the adapee
};

void TestAdapterClass();
