#include "stdafx.h"
#include "chap26_ObjectPoolTest.h"
#include <stdexcept>
#include "ObjectPool.h" 
#include "Serial.h"

#include <cstddef>
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

namespace chap26
{
  void chap26DemoTestAcquire()
  {
    FUNC_INFO;
    ObjectPool<Serial> myPool;
    auto serial = myPool.acquireObject();
    const auto fSerNumber = (serial->getSerialNumber() >= 0);
    if (fSerNumber == false)
      cout << "Serial number is not greater than 0" << endl;;
  }

  void chap26DemoTestExclusivity()
  {
    FUNC_INFO;
    ObjectPool<Serial> myPool;
    const size_t numberOfObjectsToRetrieve = 10;
    std::vector<ObjectPool<Serial>::Object> retrievedSerials;
    std::set<size_t> seenSerialNumbers;

    for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
      auto nextSerial = myPool.acquireObject();

      // Add the retrieved Serial to the vector to keep it 'alive',
      // and add the serial number to the set.
      retrievedSerials.push_back(nextSerial);
      seenSerialNumbers.insert(nextSerial->getSerialNumber());
    }

    // Assert that all retrieved serial numbers are different.
    if (numberOfObjectsToRetrieve != seenSerialNumbers.size())
      cout << "size is not the same" << endl;
  }

  void chap26DemoTestRelease()
  {
    FUNC_INFO;
    ObjectPool<Serial> myPool;
    const size_t numberOfObjectsToRetrieve = 10;

    std::vector<ObjectPool<Serial>::Object> retrievedSerials;
    for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
      // Add the retrieved Serial to the vector to keep it 'alive'.
      retrievedSerials.push_back(myPool.acquireObject());
    }
    size_t lastSerialNumber = retrievedSerials.back()->getSerialNumber();
    // Release all objects back to the pool.
    retrievedSerials.clear();

    // The above loop has created ten Serial objects, with serial
    // numbers 0-9, and released all ten Serial objects back to the pool.

    // The next loop first again retrieves ten Serial objects. The serial
    // numbers of these should all be <= lastSerialNumber.
    // The Serial object acquired after that should have a new serial number.

    bool wronglyNewObjectCreated = false;
    for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
      auto nextSerial = myPool.acquireObject();
      if (nextSerial->getSerialNumber() > lastSerialNumber) {
        wronglyNewObjectCreated = true;
        break;
      }
      retrievedSerials.push_back(nextSerial);
    }

    // Acquire one more Serial object, which should have a serial
    // number > lastSerialNumber.
    auto anotherSerial = myPool.acquireObject();
    bool newObjectCreated = (anotherSerial->getSerialNumber() > lastSerialNumber);

    assert(wronglyNewObjectCreated == false);
    assert(newObjectCreated == true);
  }
}
