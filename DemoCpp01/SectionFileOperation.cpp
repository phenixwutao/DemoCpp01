#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "SectionFileOperation.h"

using namespace std;

namespace UDemyDemo
{
  void WriteFile()
  {
    string sFileName("outputfile.txt");
    ofstream outputFile(sFileName);
    if (outputFile.is_open() == true)
    {
      outputFile << "hello testing output to a file." << endl;
      outputFile << 123;
      outputFile.close();
    }
    else
      cout << "Cannot write to file: " << sFileName << endl;
  }


  void ReadFile()
  {
    string sFileName("outputfile.txt");
    ifstream inputFile(sFileName);
    if (inputFile.is_open() == true)
    {
      while (inputFile.good())
      {
        std::string line;
        getline(inputFile, line);
        cout << line << endl;
      }
      inputFile.close();
    }
    else
      cout << "Cannot read file: " << sFileName.c_str() << endl;
  }

  void ParseFile()
  {

    string filename = "stats.txt";
    ifstream input;

    input.open(filename);

    if (!input.is_open()) {
      cout << "cannot open file: " << filename << endl;
      return;
    }

    while (input)
    {
      string line;

      getline(input, line, ':');

      int population;
      input >> population;

      // input.get();
      input >> ws;

      if (!input) {
        break;
      }

      cout << "'" << line << "'" << " -- '" << population << "'" << endl;
    }

    input.close();
  }



// PAD struct: Plain Abstract Data
#pragma pack(push, 1)

  struct Person {
    char name[50];
    int age;
    double height;
  };

#pragma pack(pop)

  void BinaryFile()
  {

    Person someone = { "Frodo", 220, 0.8 };

    string fileName = "test2.bin";

    //// Write binary file ////////////////

    ofstream outputFile;

    outputFile.open(fileName, ios::binary);

    if (outputFile.is_open())
    {

      outputFile.write(reinterpret_cast<char *>(&someone), sizeof(Person));

      outputFile.close();
    }
    else
    {
      cout << "Could not create file " + fileName;
    }

    //// Read binary file ////////////////

    Person someoneElse = {};

    ifstream inputFile;

    inputFile.open(fileName, ios::binary);

    if (inputFile.is_open())
    {

      inputFile.read(reinterpret_cast<char *>(&someoneElse), sizeof(Person));

      inputFile.close();
    }
    else
    {
      cout << "Could not read file " + fileName;
    }

    cout << someoneElse.name << ", " << someoneElse.age << ", " << someoneElse.height << endl;
  }

}
