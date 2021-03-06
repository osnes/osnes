//===-- tests/memory/TestReference.cpp - Reference Test --------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details. The Catch
// framework IS NOT distributed under LICENSE.md.
// The Catch framework is included in this project under the Boost License
// simply as a matter of convenience.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Test cases for the Reference class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/Ram.h"
#include "memory/Reference.h"

TEST_CASE("Reference read and write to Ram", "[Memory][Reference]") {
  // Build a Ram object
  std::size_t size = 100;
  std::shared_ptr<Memory::Ram<byte> > ram_p(new Memory::Ram<byte>(size));
  REQUIRE(ram_p->getSize() == size);

  // Build a reference to the memory object
  Memory::Reference<byte> ref(ram_p, 5);

  SECTION("Write data to memory with reference, and read back") {
    byte data = 7;
    // write the data at the referenced index
    ref.write(data);
    byte testData = ref.read();
    REQUIRE(testData == data);
  }

  SECTION("Copy the reference and use it to write and read data") {
    byte data = 7;
    // write the data at the referenced index
    ref.write(data);
    Memory::Reference<byte> anotherRef(ref);
    byte testData = anotherRef.read();
    REQUIRE(testData == data);
  }

  SECTION("Increment a reference and read the value") {
    // write some data to the RAM
    byte data = 8;
    ram_p->write(6, data);
    byte testData = (++ref).read();
    REQUIRE(testData == data);
  }

  SECTION("Decrement a reference and read the value") {
    // write some data to the RAM
    byte data = 9;
    ram_p->write(4, data);
    byte testData = (--ref).read();
    REQUIRE(testData == data);
  }

  SECTION("Read and write values using index offsets") {
    // write some data to the RAM
    byte data = 10;
    ram_p->write(7, data);
    // read using and index
    byte testData = ref.read(2);
    REQUIRE(testData == data);
    // write using and index
    data = 15;
    ref.write(2, data);
    testData = ram_p->read(7);
    REQUIRE(testData == data);
  }

}
