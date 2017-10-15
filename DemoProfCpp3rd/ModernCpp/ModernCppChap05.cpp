#include "StdAfx.h"

#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <string>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>

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

namespace DemoFindingElementsInRange
{
  using namespace std::string_literals;

  inline bool IsPrime(int const number)
  {
    if (((!(number & 1)) && number != 2) || (number < 2) || (number % 3 == 0 && number != 3))
      return (false);

    for (int k = 1; 36 * k*k - 12 * k < number; ++k)
      if ((number % (6 * k + 1) == 0) || (number % (6 * k - 1) == 0))
        return (false);

    return true;
  }

  void execute()
  {
    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::find(v.cbegin(), v.cend(), 3);
      if (it != v.cend()) std::cout << *it << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::find_if(v.cbegin(), v.cend(), [](int const n) {return n > 10; });
      if (it != v.cend()) std::cout << *it << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::find_if_not(v.cbegin(), v.cend(), [](int const n) {return n % 2 == 1; });
      if (it != v.cend()) std::cout << *it << std::endl;
    }

    {
      std::vector<int> v1{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 };
      std::vector<int> v2{ 1, 0, 1 };

      auto it = std::find_end(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend());

      if (it != v1.cend())
        std::cout << "found at index "
        << std::distance(v1.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };
      std::vector<int> p{ 5, 7, 11 };

      auto it = std::find_first_of(
        v.cbegin(), v.cend(),
        p.cbegin(), p.cend());

      if (it != v.cend())
        std::cout << "found " << *it
        << " at index " << std::distance(v.cbegin(), it)
        << std::endl;
    }

    {
      auto text = "The quick brown fox jumps over the lazy dog"s;
      auto word = "over"s;

      auto it = std::search(
        text.cbegin(), text.cend(),
        word.cbegin(), word.cend());

      if (it != text.cend())
        std::cout << "found " << word
        << " at index " << std::distance(text.cbegin(), it)
        << std::endl;
    }

    {
#ifdef SEARCHERS_AVAILABLE
      auto text = "The quick brown fox jumps over the lazy dog"s;
      auto word = "over"s;

      auto it = std::search(
        text.cbegin(), text.cend(),
        std::make_boyer_moore_searcher(word.cbegin(), word.cend()));

      if (it != text.cend())
        std::cout << "found " << word
        << " at index " << std::distance(text.cbegin(), it)
        << std::endl;
#endif
    }

    {
      std::vector<int> v{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 };

      auto it = std::search_n(v.cbegin(), v.cend(), 2, 0);

      if (it != v.cend())
        std::cout << "found at index " << std::distance(v.cbegin(), it)
        << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::adjacent_find(v.cbegin(), v.cend());
      if (it != v.cend())
        std::cout << "found at index " << std::distance(v.cbegin(), it)
        << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::adjacent_find(
        v.cbegin(), v.cend(),
        [](int const a, int const b) {return IsPrime(a) && IsPrime(b); });

      if (it != v.cend())
        std::cout << "found at index " << std::distance(v.cbegin(), it)
        << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto success = std::binary_search(v.cbegin(), v.cend(), 8);

      if (success) std::cout << "found" << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::lower_bound(v.cbegin(), v.cend(), 1);

      if (it != v.cend())
        std::cout << "lower bound at "
        << std::distance(v.cbegin(), it)
        << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto it = std::upper_bound(v.cbegin(), v.cend(), 1);

      if (it != v.cend())
        std::cout << "upper bound at "
        << std::distance(v.cbegin(), it)
        << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto bounds = std::equal_range(v.cbegin(), v.cend(), 1);

      std::cout << "range between indexes "
        << std::distance(v.cbegin(), bounds.first)
        << " and "
        << std::distance(v.cbegin(), bounds.second)
        << std::endl;
    }
  }
}

void Ch05_DemoFindingElementsInRange()
{
  FUNC_INFO;
  DemoFindingElementsInRange::execute();
}


namespace DemoSortingRange
{
  using namespace std::string_literals;

  struct Task
  {
    int priority;
    std::string name;
  };

  bool operator<(Task const & lhs, Task const & rhs)
  {
    return (lhs.priority < rhs.priority);
  }

  bool operator>(Task const & lhs, Task const & rhs)
  {
    return (lhs.priority > rhs.priority);
  }

  //bool operator==(Task const & lhs, Task const & rhs)
  //{
  //  return ((lhs.priority == rhs.priority) && (lhs.name == rhs.name));
  //}

  template<typename T>
  void PrintVector(vector<T> const & v)
  {
    for (auto item : v)
    {
      cout << item << " ";
    }
    cout << endl;
  }

  template<>
  void PrintVector(vector<Task> const & v)
  {
    for (const Task & item : v)
    {
      cout << "[" << item.priority << " : " << item.name << "]" << endl;;
    }
  }

  void execute()
  {
    {
      PASS_INFO(1);
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

      std::sort(v.begin(), v.end());
      // v = {1, 1, 2, 3, 5, 8, 13}
      PrintVector(v);

      std::sort(v.begin(), v.end(), std::greater<>());
      // v = {13, 8, 5, 3, 2, 1 ,1}
      PrintVector(v);
    }

    {
      PASS_INFO(2);
      std::vector<Task> v{
        { 10, "Task 1"s },
        { 40, "Task 2"s },
        { 25, "Task 3"s },
        { 10, "Task 4"s },
        { 80, "Task 5"s },
        { 10, "Task 6"s },
      };

      std::stable_sort(v.begin(), v.end());
      // {{ 10, "Task 1" },{ 10, "Task 4" },{ 10, "Task 6" },
      //  { 25, "Task 3" },{ 40, "Task 2" },{ 80, "Task 5" }}
      PrintVector(v);

      std::stable_sort(v.begin(), v.end(), std::greater<>());
      // {{ 80, "Task 5" },{ 40, "Task 2" },{ 25, "Task 3" },
      //  { 10, "Task 1" },{ 10, "Task 4" },{ 10, "Task 6" }}
      PrintVector(v);
    }

    {
      PASS_INFO(3);
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

      std::partial_sort(v.begin(), v.begin() + 4, v.end());
      // v = {1, 1, 2, 3, ?, ?, ?}
      PrintVector(v);

      std::partial_sort(v.begin(), v.begin() + 4, v.end(), std::greater<>());
      // v = {13, 8, 5, 3, ?, ?, ?}
      PrintVector(v);
    }

    {
      PASS_INFO(4);
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
      std::vector<int> vc(v.size());

      std::partial_sort_copy(v.begin(), v.end(), vc.begin(), vc.end());
      // v  = {3, 13, 5, 8, 1, 2, 1}
      // vc = {1, 1, 2, 3, 5, 8, 13}
      PrintVector(v);
      PrintVector(vc);

      std::partial_sort_copy(v.begin(), v.end(), vc.begin(), vc.end(), std::greater<>());
      // vc = {13, 8, 5, 3, 2, 1, 1}
      PrintVector(vc);
    }

    {
      PASS_INFO(5);
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

      std::nth_element(v.begin(), v.begin() + 3, v.end());
      // v = {1, 1, 2, 3, 5, 8, 13}
      PrintVector(v);

      std::nth_element(v.begin(), v.begin() + 3, v.end(), std::greater<>());
      // v = {13, 8, 5, 3, 2, 1, 1}
      PrintVector(v);
    }

    {
      PASS_INFO(6);
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      auto sorted = std::is_sorted(v.cbegin(), v.cend());
      cout << "sorted " << (sorted ? "Yes" : "No") << endl;

      sorted = std::is_sorted(v.cbegin(), v.cend(), std::greater<>());
      cout << "sorted " << (sorted ? "Yes" : "No") << endl;
    }

    {
      PASS_INFO(7);
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };

      auto it = std::is_sorted_until(v.cbegin(), v.cend());

      auto length = std::distance(v.cbegin(), it);
      cout << "length " << length << endl;
    }
  }
}

void Ch05_DemoSortingRange()
{
  FUNC_INFO;
  DemoSortingRange::execute();
}


#include <numeric>
#include <random>

namespace DemoInitializingRange
{
  template<typename T>
  void PrintSet(vector<T> const & v)
  {
    for (const auto & item : v)
      cout << item << " ";
    cout << endl;
  }

  void execute()
  {
    {
      std::vector<int> v(5);
      std::fill(v.begin(), v.end(), 42);
      // v = {42, 42, 42, 42, 42}
      PrintSet(v);

      std::array<int, 5> a;
      std::fill(a.begin(), a.end(), 42);
      // a = {42, 42, 42, 42, 42}
    }

    {
      std::vector<int> v(10);
      std::fill_n(v.begin(), 5, 42);
      // v = {42, 42, 42, 42, 42, 0, 0, 0, 0, 0}
      PrintSet(v);
    }

    {
      std::random_device rd{};
      std::mt19937 mt{ rd() };
      std::uniform_int_distribution<> ud{ 1, 10 };

      std::vector<int> v(5);

      std::generate(v.begin(), v.end(), [&ud, &mt] {return ud(mt); });
      PrintSet(v);
    }

    {
      std::vector<int> v(5);

      auto i = 1;
      std::generate_n(v.begin(), v.size(), [&i] { return i*i++; });
      // v = {1, 4, 9, 16, 25}
      PrintSet(v);
    }

    {
      std::vector<int> v(5);

      std::iota(v.begin(), v.end(), 1);
      // v = {1, 2, 3, 4, 5}
      PrintSet(v);
    }
  }
}

void Ch05_DemoInitializingRange()
{
  FUNC_INFO;
  DemoInitializingRange::execute();
}

namespace DemoUsingSetOperationsOnRange
{
  using namespace std::string_literals;

  struct Task
  {
    int priority;
    std::string name;
  };

  bool operator<(Task const & lhs, Task const & rhs)
  {
    return lhs.priority < rhs.priority;
  }

  bool operator>(Task const & lhs, Task const & rhs)
  {
    return lhs.priority > rhs.priority;
  }

  template<typename T>
  void PrintVector(vector<T> const & v)
  {
    for (auto item : v)
    {
      cout << item << " ";
    }
    cout << endl;
  }

  template<>
  void PrintVector(vector<Task> const & v)
  {
    for (const Task & item : v)
    {
      cout << "[" << item.priority << " : " << item.name << "]" << endl;;
    }
  }

  void execute()
  {
    {
      printf("************ union ************\n");
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_union(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v3));

      // v3 = {1, 2, 3, 3, 4, 4, 5, 6, 8}
      PrintVector(v3);
    }

    {
      printf("************ merge ************\n");
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::merge(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v3));

      // v3 = {1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 8}
      PrintVector(v3);
    }

    {
      printf("************ intersection ************\n");
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_intersection(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v3));

      // v3 = {2, 3, 4}
      PrintVector(v3);
    }

    {
      printf("************ difference ************\n");
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_difference(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v3));

      // v3 = {1, 4, 5}
      PrintVector(v3);
    }

    {
      printf("************ symmetric difference ************\n");
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_symmetric_difference(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v3));

      // v3 = {1, 3, 4, 5, 6, 8}
      PrintVector(v3);
    }

    {
      printf("************ set include ************\n");
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3{ 1, 2, 4 };
      std::vector<int> v4{};

      auto i1 = std::includes(v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend()); // i1 = false
      auto i2 = std::includes(v1.cbegin(), v1.cend(),
        v3.cbegin(), v3.cend()); // i2 = true
      auto i3 = std::includes(v1.cbegin(), v1.cend(),
        v4.cbegin(), v4.cend()); // i3 = true
      cout << "i1 " << i1 << " i2 " << i2 << " i3 " << i3 << endl;
    }

    {
      std::vector<Task> v1{
        { 10, "Task 1.1"s },
        { 20, "Task 1.2"s },
        { 20, "Task 1.3"s },
        { 20, "Task 1.4"s },
        { 30, "Task 1.5"s },
        { 50, "Task 1.6"s },
      };

      std::vector<Task> v2{
        { 20, "Task 2.1"s },
        { 30, "Task 2.2"s },
        { 30, "Task 2.3"s },
        { 30, "Task 2.4"s },
        { 40, "Task 2.5"s },
        { 50, "Task 2.6"s },
      };

      printf("************ union ************\n");
      std::vector<Task> v3;
      std::set_union(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v3));
      // v3 = {{ 10, "Task 1.1" },{ 20, "Task 1.2" },{ 20, "Task 1.3" },
      //       { 20, "Task 1.4" },{ 30, "Task 1.5" },{ 30, "Task 2.3" },
      //       { 30, "Task 2.4" },{ 40, "Task 2.5" },{ 50, "Task 1.6" }}
      PrintVector(v3);

      printf("************ merge ************\n");
      std::vector<Task> v4;
      std::merge(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v4));
      // v4 = {{ 10, "Task 1.1" },{ 20, "Task 1.2" },{ 20, "Task 1.3" },
      //       { 20, "Task 1.4" },{ 20, "Task 2.1" },{ 30, "Task 1.5" },
      //       { 30, "Task 2.2" },{ 30, "Task 2.3" },{ 30, "Task 2.4" },
      //       { 40, "Task 2.5" },{ 50, "Task 1.6" },{ 50, "Task 2.6" }}
      PrintVector(v4);

      printf("************ intersection ************\n");
      std::vector<Task> v5;
      std::set_intersection(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v5));
      // v5 = {{ 20, "Task 1.2" },{ 30, "Task 1.5" },{ 50, "Task 1.6" }}
      PrintVector(v5);

      printf("************ difference ************\n");
      std::vector<Task> v6;
      std::set_difference(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v6));
      // v6 = {{ 10, "Task 1.1" },{ 20, "Task 1.3" },{ 20, "Task 1.4" }}
      PrintVector(v6);

      printf("************ symmetric difference ************\n");
      std::vector<Task> v7;
      std::set_symmetric_difference(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        std::back_inserter(v7));
      // v7 = {{ 10, "Task 1.1" },{ 20, "Task 1.3" },{ 20, "Task 1.4" }
      //       { 30, "Task 2.3" },{ 30, "Task 2.4" },{ 40, "Task 2.5" }}
      PrintVector(v7);

    }
  }
}

void Ch05_DemoUsingSetOperationsOnRange()
{
  FUNC_INFO;
  DemoUsingSetOperationsOnRange::execute();
}

void Ch05_DemoUsingIteratorsInsertNewElements()
{
  FUNC_INFO;
  auto printVector = [&](const vector<int>& v)
  {
    for (const auto& it : v)
      cout << it << " ";
    cout << endl;
  };

  auto printList = [&](const list<int>& v)
  {
    for (const auto& it : v)
      cout << it << " ";
    cout << endl;
  };

  {
    PASS_INFO(1);
    std::vector<int> v{ 1,2,3,4,5 };
    std::fill_n(std::back_inserter(v), 3, 0);

    // v={1,2,3,4,5,0,0,0}
    printVector(v);
  }

  {
    PASS_INFO(2);
    std::list<int> l{ 1,2,3,4,5 };
    std::fill_n(std::front_inserter(l), 3, 0);

    // l={0,0,0,1,2,3,4,5}
    printList(l);
  }

  {
    PASS_INFO(3);
    std::vector<int> v{ 1,2,3,4,5 };
    std::fill_n(std::inserter(v, v.begin()), 3, 0);

    // v={0,0,0,1,2,3,4,5}
    printVector(v);
  }

  {
    PASS_INFO(4);
    std::list<int> l{ 1,2,3,4,5 };
    auto it = l.begin();
    std::advance(it, 3);

    std::fill_n(std::inserter(l, it), 3, 0);

    // l={1,2,3,0,0,0,4,5}
    printList(l);
  }

  {
    PASS_INFO(5);
    std::vector<int> v{ 1,2,3,4,5 };
    std::back_insert_iterator<std::vector<int>> it(v);
    *it = 6;
    printVector(v);
  }

  {
    PASS_INFO(6);
    std::list<int> l{ 1,2,3,4,5 };
    std::front_insert_iterator<std::list<int>> it(l);
    *it = 0;
    printList(l);
  }

  {
    PASS_INFO(7);
    std::vector<int> v{ 1,2,3,4,5 };
    *std::back_inserter(v) = 6;
    printVector(v);
  }

  {
    PASS_INFO(8);
    std::list<int> l{ 1,2,3,4,5 };
    *std::front_inserter(l) = 0;
    printList(l);
  }
}

#include <cassert>
#include <memory>

namespace DemoWritingYourOwnRandomAccessIterator
{
  using namespace std::string_literals;

  struct Task
  {
    int priority;
    std::string name;
  };

  struct Tag
  {
    int id;
    std::string name;

    Tag(int const id = 0, std::string const & name = ""s) :
      id(id), name(name)
    {}
  };

  template <typename Type, size_t const SIZE>
  class dummy_array
  {
    Type data[SIZE] = {};

  public:
    Type& operator[](size_t const index)
    {
      if (index < SIZE) return data[index];
      throw std::out_of_range("index out of range");
    }

    Type const & operator[](size_t const index) const
    {
      if (index < SIZE) return data[index];
      throw std::out_of_range("index out of range");
    }

    size_t size() const { return SIZE; }

    template <typename T, size_t const Size>
    class dummy_array_iterator
    {
    public:
      typedef dummy_array_iterator              self_type;
      typedef T                                 value_type;
      typedef T&                                reference;
      typedef T*                                pointer;
      typedef std::random_access_iterator_tag   iterator_category;
      typedef ptrdiff_t                         difference_type;

    private:
      pointer  ptr = nullptr;
      size_t   index = 0;

      bool compatible(self_type const & other) const
      {
        return ptr == other.ptr;
      }

    public:
      explicit dummy_array_iterator(pointer ptr, size_t const index) :
        ptr(ptr), index(index)
      {
      }

      // --- common to all iterators ---
      // copy-constructible, copy-assignable and destructible
      dummy_array_iterator(dummy_array_iterator const & o) = default;
      dummy_array_iterator& operator=(dummy_array_iterator const & o) = default;
      ~dummy_array_iterator() = default;

      // can be prefix- and postfix- incremented
      self_type & operator++ ()
      {
        if (index >= Size)
          throw std::out_of_range("Iterator cannot be incremented past the end of range.");
        ++index;
        return *this;
      }

      self_type operator++ (int)
      {
        self_type tmp = *this;
        ++*this;
        return tmp;
      }
      // --- common to all iterators ---

      // --- input iterator ---
      // supports equality/inequality comparisons
      bool operator== (self_type const & other) const
      {
        assert(compatible(other));
        return index == other.index;
      }

      bool operator!= (self_type const & other) const
      {
        return !(*this == other);
      }

      // can be dereferenced as an rvalue
      reference operator* () const
      {
        if (ptr == nullptr)
          throw std::bad_function_call();
        return *(ptr + index);
      }

      reference operator-> () const
      {
        if (ptr == nullptr)
          throw std::bad_function_call();
        return *(ptr + index);
      }

      // --- input iterator ---

      // --- output iterator ---
      // can be dereferenced as an lvalue
      // --- output iterator ---

      // --- forward iterator ---
      // default-constructible
      dummy_array_iterator() = default;

      // multi-pass: neither dereferencing nor incrementing affects dereferenceability
      // --- forward iterator ---

      // --- bidirectional iterator ---
      // can be decremented
      self_type & operator--()
      {
        if (index <= 0)
          throw std::out_of_range("Iterator cannot be decremented past the end of range.");
        --index;
        return *this;
      }

      self_type operator--(int)
      {
        self_type tmp = *this;
        --*this;
        return tmp;
      }
      // --- bidirectional iterator ---

      // --- random access iterator ---
      // supports arithmetic operators + and -
      self_type operator+(difference_type offset) const
      {
        self_type tmp = *this;
        return tmp += offset;
      }

      self_type operator-(difference_type offset) const
      {
        self_type tmp = *this;
        return tmp -= offset;
      }

      difference_type operator-(self_type const & other) const
      {
        assert(compatible(other));
        return (index - other.index);
      }

      // supports inequality comparisons (<, >, <= and >=) between iterators
      bool operator<(self_type const & other) const
      {
        assert(compatible(other));
        return index < other.index;
      }

      bool operator>(self_type const & other) const
      {
        return other < *this;
      }

      bool operator<=(self_type const & other) const
      {
        return !(other < *this);
      }

      bool operator>=(self_type const & other) const
      {
        return !(*this < other);
      }

      // supports compound assignment operations += and -=
      self_type & operator+=(difference_type const offset)
      {
        if (index + offset < 0 || index + offset > Size)
          throw std::out_of_range("Iterator cannot be incremented past the end of range.");

        index += offset;
        return *this;
      }

      self_type & operator-=(difference_type const offset)
      {
        return *this += -offset;
      }

      // supports offset dereference operator ([])
      value_type & operator[](difference_type const offset)
      {
        return (*(*this + offset));
      }

      value_type const & operator[](difference_type const offset) const
      {
        return (*(*this + offset));
      }
      // --- random access iterator ---
    };

    typedef dummy_array_iterator<Type, SIZE>        iterator;
    typedef dummy_array_iterator<Type const, SIZE>  constant_iterator;

  public:
    iterator begin()
    {
      return iterator(data, 0);
    }

    iterator end()
    {
      return iterator(data, SIZE);
    }

    constant_iterator begin() const
    {
      return constant_iterator(data, 0);
    }

    constant_iterator end() const
    {
      return constant_iterator(data, SIZE);
    }
  };

  int func(int i) { return 2*i; }

  void execute()
  {
    {
      dummy_array<int, 5> a;
      a[0] = 1;
      a[1] = 2;
      a[2] = 3;
      a[3] = 4;
      a[4] = 5;
      dummy_array<int, 5> b;

      dummy_array<int, 5>::iterator i1 = a.begin();
      dummy_array<int, 5>::iterator i2 = a.begin();
      dummy_array<int, 5>::iterator i3 = a.begin();
      dummy_array<int, 5>::iterator i4 = a.end();

      dummy_array<int, 5>::iterator y1 = b.begin();

      // copy-constructible, copy-assignable and destructible
      auto ci1(i1);
      ci1 = i3;

      // incrementable
      ++ci1;
      ci1++;

      // equality/inequality comparison
      auto e1 = i1 == i2;
      auto e2 = i1 == i3;
      //auto e3 = i1 == y1;

      // dereferenced as rvalue
      if (*i1 > 0) {}

      // dereferenced as lvalue
      *i1 = 11;
      *i1++ = 111;

      // default constructible
      dummy_array<int, 5>::iterator i0;
      dummy_array<int, 5>::iterator();

      // multi-pass
      {
        i2 = i1;
        *i1++;
        *i2;
      }

      // decrementable
      --i4;
      i4--;
      *i4--;

      // arithmetic increment and decrement
      auto x1 = i1 + 2;
      //auto x2 = 1 + i1;
      auto x3 = i4 - 1;
      auto d = x1 - x3;

      // logical comparison
      auto ls = i1 < i4;
      auto gt = i1 > i4;
      auto le = i1 <= i4;
      auto ge = i1 >= i4;

      // compound assignment
      i1 += 2;
      i1 += -2;
      i1 -= -2;
      i1 -= 2;

      // offset dereference operator
      auto e = i1[2];
    }

    {
      //dummy_array<int, 5> a;
      vector<int> a;  a.resize(5);
      a[0] = 10;
      a[1] = 20;
      a[2] = 30;
      a[3] = 40;
      a[4] = 50;
      std::transform(a.begin(), a.end(), a.begin(), [](int e) ->int {return e * 2; });

      for (auto&& e : a) std::cout << e << std::endl;
    }

    {
      dummy_array<int, 5> a;
      a[0] = 10;
      a[1] = 20;
      a[2] = 30;
      a[3] = 40;
      a[4] = 50;

      for (auto&& e : a) std::cout << e << std::endl;

      auto lp = [](dummy_array<int, 5> const & ca)
      {
        for (auto const & e : ca)
          std::cout << e << std::endl;
      };

      lp(a);
    }

    {
      dummy_array<Task, 5> a;
      a[0] = Task{ 10, "Task 1" };
      a[1] = Task{ 20, "Task 2" };
      a[2] = Task{ 30, "Task 3" };
      a[3] = Task{ 40, "Task 4" };
      a[4] = Task{ 50, "Task 5" };

      for (auto&& e : a)
        std::cout << e.priority << " " << e.name << std::endl;

      auto p0 = &a[0];
      std::cout << p0->priority << " " << p0->name << std::endl;
    }

    {
      dummy_array<std::unique_ptr<Tag>, 5> a;
      a[0] = std::make_unique<Tag>(1, "Tag 1");
      a[1] = std::make_unique<Tag>(2, "Tag 2");
      a[2] = std::make_unique<Tag>(3, "Tag 3");
      a[3] = std::make_unique<Tag>(4, "Tag 4");
      a[4] = std::make_unique<Tag>(5, "Tag 5");

      for (auto it = a.begin(); it != a.end(); ++it)
        std::cout << it->id << " " << it->name << std::endl;

      auto p0 = a[0].get();
      std::cout << p0->id << " " << p0->name << std::endl;
    }

    {
      dummy_array<int, 5> a;
      a[0] = 10;
      a[1] = 20;
      a[2] = 30;
      a[3] = 40;
      a[4] = 50;

      auto lp = [](dummy_array<int, 5> const & arr)
      {
        for (size_t i = 0; i < arr.size(); ++i)
        {
          std::cout << arr[i] << std::endl;
        }
      };

      lp(a);
    }
  }
}


void Ch05_DemoWritingYourOwnRandomAccessIterator()
{
  DemoWritingYourOwnRandomAccessIterator::execute();
}

