#include "StdAfx.h"

#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <string>
#include <stack>
#include <bitset>

#include "ModernCpp.h"

using namespace std;

namespace DemoUsingVectorAsDefaultContainer
{
  using namespace std::string_literals;
  unsigned int kPass = 0;
  void process(int const * const arr, int const size)
  {
    PASS_INFO(kPass++);
    for (int i = 0; i < size; ++i)
      std::cout << arr[i] << std::endl;
    std::cout << std::endl;
  }

  struct foo
  {
    int a;
    double b;
    std::string c;

    foo(int a, double b, std::string const & c) :
      a(a), b(b), c(c)
    {}
  };

  void execute()
  {
    {
      std::vector<int> v1{ 1, 2, 3, 4, 5 };

      int arr[] = { 1, 2, 3, 4, 5 };
      std::vector<int> v2(arr, arr + 5);

      std::list<int> l{ 1, 2, 3, 4, 5 };
      std::vector<int> v3(l.begin(), l.end());

      std::vector<int> v4(5, 1);
    }

    {
      std::vector<int> v1{ 1, 2, 3, 4, 5 };
      v1.push_back(6);
      v1.pop_back();

      int arr[] = { 1, 2, 3, 4, 5 };
      std::vector<int> v2;
      v2.insert(v2.begin(), arr, arr + 5);

      std::vector<foo> v3;
      v3.emplace_back(1, 1.0, "one"s);
      v3.emplace(v3.begin(), 2, 2.0, "two"s);
    }

    {
      std::vector<int> v1{ 1, 2, 3, 4, 5 };
      std::vector<int> v2{ 10, 20, 30 };
      v2 = v1;

      int arr[] = { 1, 2, 3, 4, 5 };
      std::vector<int> v3;
      v3.assign(arr, arr + 5);

      std::vector<int> v4{ 1, 2, 3, 4, 5 };
      std::vector<int> v5{ 10, 20, 30 };
      v4.swap(v5);

      std::vector<int> v6{ 1, 2, 3, 4, 5 };
      v6.clear();

      std::vector<int> v7{ 1, 2, 3, 4, 5 };
      v7.erase(v7.begin() + 2, v7.begin() + 4);
    }

    {
      std::vector<int> v{ 1, 2, 3, 4, 5 };

      process(v.data(), static_cast<int>(v.size()));
      process(&v[0], static_cast<int>(v.size()));
      process(&v.front(), static_cast<int>(v.size()));
      process(&*v.begin(), static_cast<int>(v.size()));
    }

    {
      std::list<int> l{ 1, 2, 3, 4, 5 };
      std::vector<int> v(l.begin(), l.end());
      process(v.data(), static_cast<int>(v.size()));
    }

    {
      std::vector<int> v{ 1, 2, 3, 4, 5 };
      std::vector<int>().swap(v);
    }
  }
}

void Ch05_DemoUsingVectorAsDefaultContainer()
{
  FUNC_INFO;
  DemoUsingVectorAsDefaultContainer::execute();
}

namespace DemoUsingBitsetForFixedSizeSequences
{
  using namespace std::string_literals;

#define BORDER_NONE     0x00
#define BORDER_LEFT     0x01
#define BORDER_TOP      0x02
#define BORDER_RIGHT    0x04
#define BORDER_BOTTOM   0x08

  struct border_flags
  {
    static const int left = 0;
    static const int top = 1;
    static const int right = 2;
    static const int bottom = 3;
  };

  void apply_style(unsigned int const style)
  {
    if (style & BORDER_BOTTOM) {}
  }

  template <size_t N>
  std::vector<unsigned long> bitset_to_vectorulong(std::bitset<N> bs)
  {
    auto result = std::vector<unsigned long>{};
    auto const size = 8 * sizeof(unsigned long);
    auto const mask = std::bitset<N>{ static_cast<unsigned long>(-1) };

    auto totalbits = 0;
    while (totalbits < N)
    {
      auto value = (bs & mask).to_ulong();
      result.push_back(value);
      bs >>= size;
      totalbits += size;
    }

    return result;
  }

  void execute()
  {
    // construct
    {
      std::bitset<8> b1;            // [0,0,0,0,0,0,0,0]

      std::bitset<8> b2{ 10 };      // [0,0,0,0,1,0,1,0]

      std::bitset<8> b3{ "1010"s }; // [0,0,0,0,1,0,1,0]

      std::bitset<8> b4{ "ooooxoxo"s, 0, std::string::npos, 'o', 'x' };
      // [0,0,0,0,1,0,1,0]
    }

    // element access
    {
      std::bitset<8> bs{ 10 };
      std::cout << "has " << bs.count() << " 1s" << std::endl;

      if (bs.any()) std::cout << "has some 1s" << std::endl;
      if (bs.all()) std::cout << "has only 1s" << std::endl;
      if (bs.none()) std::cout << "has no 1s" << std::endl;

      if (!bs.test(0)) std::cout << "even" << std::endl;
      if (!bs[0]) std::cout << "even" << std::endl;
    }

    // modifiers
    {
      std::bitset<8> b1{ 42 }; // [0,0,1,0,1,0,1,0]
      std::bitset<8> b2{ 11 }; // [0,0,0,0,1,0,1,1]

      auto b3 = b1 | b2;       // [0,0,1,0,1,0,1,1]
      auto b4 = b1 & b2;       // [0,0,0,0,1,0,1,0]
      auto b5 = b1 ^ b2;       // [1,1,0,1,1,1,1,0]
      auto b6 = ~b1;           // [1,1,0,1,0,1,0,1]

      auto b7 = b1 << 2;       // [1,0,1,0,1,0,0,0]
      auto b8 = b1 >> 2;       // [0,0,0,0,1,0,1,0]

      b1.flip();               // [1,1,0,1,0,1,0,1]
      b1.flip(0);              // [1,1,0,1,0,1,0,0]
      b1.set(0, true);         // [1,1,0,1,0,1,0,1]
      b1.set(0, false);        // [1,1,0,1,0,1,0,0]
      b1.reset(2);             // [1,1,0,1,0,0,0,0]
    }

    // conversion
    {
      std::bitset<8> bs{ 42 };

      auto n1 = bs.to_ulong();   // n1 = 42UL
      auto n2 = bs.to_ullong();  // n2 = 42ULL

      auto s1 = bs.to_string();           // s1 = "00101010"
      auto s2 = bs.to_string('o', 'x');   // s2 = "ooxoxoxo"
    }

    // C-like style
    {
      // initialize with no flags
      unsigned int style = BORDER_NONE;
      // set a flag
      style = BORDER_BOTTOM;
      // add more flags
      style |= BORDER_LEFT | BORDER_RIGHT | BORDER_TOP;
      // remove some flags
      style &= ~BORDER_LEFT;
      style &= ~BORDER_RIGHT;
      // test if a flag is set
      if ((style & BORDER_BOTTOM) == BORDER_BOTTOM) {}
      // pass the flags as argument to a function
      apply_style(style);
    }

    // C++ style
    {
      // initialize with no flags
      std::bitset<4> style;
      // set a flag
      style.set(border_flags::bottom);
      // set more flags
      style
        .set(border_flags::left)
        .set(border_flags::top)
        .set(border_flags::right);
      // remove some flags
      style[border_flags::left] = 0;
      style.reset(border_flags::right);
      // test if a flag is set
      if (style.test(border_flags::bottom)) {}
      // pass the flags as argument to a function
      apply_style(style.to_ulong());
    }

    {
      std::bitset<128> bs =
        (std::bitset<128>(0xFEDC) << 96) |
        (std::bitset<128>(0xBA98) << 64) |
        (std::bitset<128>(0x7654) << 32) |
        std::bitset<128>(0x3210);

      std::cout << bs << std::endl;

      auto result = bitset_to_vectorulong(bs);
      for (auto const v : result)
        std::cout << std::hex << v << std::endl;

      std::cout << std::dec;
    }
  }
}

void Ch05_DemoUsingBitsetForFixedSizeSequences()
{
  FUNC_INFO;
  DemoUsingBitsetForFixedSizeSequences::execute();
}

namespace DemoUsingVectorBoolForBitSequences
{
  class bitvector
  {
    std::vector<bool> bv;
  public:
    bitvector() = default;                              // constructor
    bitvector(bitvector const &) = default;             // copy constructor
    bitvector(bitvector&&) = default;                   // move constructor
    bitvector& operator=(bitvector const &) = default;  // copy assignment operator
    bitvector& operator=(bitvector&&) = default;        // move assignment operator

    bitvector(std::vector<bool> const & bv) : bv(bv) {} // constructor with argument
    bool operator[](size_t const i) { return bv[i]; }   // [] operator

    inline bool any() const
    {
      for (auto b : bv)
        if (b) return true;
      return false;
    }

    inline bool all() const
    {
      for (auto b : bv)
        if (!b) return false;
      return true;
    }

    inline bool none() const
    { return !any(); }

    inline size_t count() const
    {
      return std::count(bv.cbegin(), bv.cend(), true);
    }

    inline size_t size() const
    { return bv.size(); }

    inline bitvector & add(bool const value)
    {
      bv.push_back(value);
      return *this;
    }

    inline bitvector & remove(size_t const index)
    {
      if (index >= bv.size())
        throw std::out_of_range("Index out of range");
      bv.erase(bv.begin() + index);
      return *this;
    }

    inline bitvector & set(bool const value = true)
    {
      for (size_t i = 0; i < bv.size(); ++i)
        bv[i] = value;
      return *this;
    }

    inline bitvector & set(size_t const index, bool const value = true)
    {
      if (index >= bv.size())
        throw std::out_of_range("Index out of range");
      bv[index] = value;
      return *this;
    }

    inline bitvector & reset()
    {
      for (size_t i = 0; i < bv.size(); ++i) 
        bv[i] = false;
      return *this;
    }

    inline bitvector & reset(size_t const index)
    {
      if (index >= bv.size())
        throw std::out_of_range("Index out of range");
      bv[index] = false;
      return *this;
    }

    inline bitvector & flip()
    {
      bv.flip();
      return *this;
    }

    std::vector<bool>& data() { return bv; }
  };

  void execute()
  {
    {
      // create an empty vector
      std::vector<bool> bv;      // []

                                 // add bits to the vector
      bv.push_back(true);        // [1]
      bv.push_back(true);        // [1, 1]
      bv.push_back(false);       // [1, 1, 0]
      bv.push_back(false);       // [1, 1, 0, 0]
      bv.push_back(true);        // [1, 1, 0, 0, 1]

                                 // set values of individual bits
      bv[3] = true;              // [1, 1, 0, 1, 1]

      // use generic algorithms
      auto count_of_ones = std::count(bv.cbegin(), bv.cend(), true);

      // remove a bit from the vector
      bv.erase(bv.begin() + 2);  // [1, 1, 1, 1]
    }

    {
      std::vector<bool> bv;
      bv.resize(10);
      // auto& bit1 = bv[0]; // error
      // auto& bit2 = *bv.begin(); // error
    }

    {
      bitvector bv;
      bv.add(true).add(true).add(false);  // [1, 1, 0]
      bv.add(false);                      // [1, 1, 0, 0]
      bv.add(true);                       // [1, 1, 0, 0, 1]

      if (bv.any()) std::cout << "has some 1s" << std::endl;
      if (bv.all()) std::cout << "has only 1s" << std::endl;
      if (bv.none()) std::cout << "has no 1s" << std::endl;
      std::cout << "has " << bv.count() << " 1s" << std::endl;

      bv.set(2, true);  // [1, 1, 1, 0, 1]
      bv.set();         // [1, 1, 1, 1, 1]

      bv.reset(0);      // [0, 1, 1, 1, 1]
      bv.reset();       // [0, 0, 0, 0, 0]

      bv.flip();        // [1, 1, 1, 1, 1]
    }
  }
}

void Ch05_DemoUsingVectorBoolForBitSequences()
{
  FUNC_INFO;
  DemoUsingVectorBoolForBitSequences::execute();
}

