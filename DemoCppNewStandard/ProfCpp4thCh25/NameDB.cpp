#include "stdafx.h"
#include "NameDB.h"
#include <stdexcept>
#include <fstream>

using namespace std;

namespace chap25
{
  // Reads the names from the file and populates the database.
  // The database is a map associating names with their frequency.
  NameDB::NameDB(string_view nameFile)
  {
    // Open the file and check for errors.
    ifstream inputFile(nameFile.data());
    if (!inputFile) {
      string errText = "Unable to open file: ";
      errText += nameFile.data();
      throw invalid_argument(errText);
    }

    // Read the names one at a time.
    string name;
    while (inputFile >> name) {
      ++mNames[name];
    }
  }

  // Returns the rank of the name.
  // First looks up the name to obtain the number of babies with that name.
  // Then iterates through all the names, counting all the names with a higher
  // count than the specified name. Returns that count as the rank.
  int NameDB::getNameRank(string_view name) const
  {
    int num = getAbsoluteNumber(name);

    // Check if we found the name.
    if (num == -1) {
      return -1;
    }

    // Now count all the names in the map that have 
    // count higher than this one. If no name has a higher count,
    // this name is rank number 1. Every name with a higher count
    // decreases the rank of this name by 1.
    int rank = 1;
    for (auto& entry : mNames) {
      if (entry.second > num) {
        rank++;
      }
    }

    return rank;
  }

  // Returns the count associated with this name.
  int NameDB::getAbsoluteNumber(string_view name) const
  {
    auto res = mNames.find(name.data());
    if (res != end(mNames)) {
      return res->second;
    }

    return -1;
  }
}
