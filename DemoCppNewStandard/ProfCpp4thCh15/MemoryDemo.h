#pragma once

#include <cstddef>
#include <new>

namespace Tut2
{
  class MemoryDemo
  {
  public:
    virtual ~MemoryDemo() = default;

    // overload new/delete operator
    void* operator new(size_t size);
    void operator delete(void* ptr) noexcept;

    // overload new/delete array operator
    void* operator new[](size_t size);
    void operator delete[](void* ptr) noexcept;

    // overload new/delete nothrow operator
    void* operator new(size_t size, const std::nothrow_t&) noexcept;
    void operator delete(void* ptr, const std::nothrow_t&) noexcept;

    // overload new/delete nothrow array operator
    void* operator new[](size_t size, const std::nothrow_t&) noexcept;
    void operator delete[](void* ptr, const std::nothrow_t&) noexcept;


    void* operator new(size_t size, int extra);
    void operator delete(void* ptr, int extra) noexcept;
  };
}
