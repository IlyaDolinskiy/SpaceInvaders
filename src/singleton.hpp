#pragma once
#include <iostream>

template<typename T>
class Singleton
{
public:
  static T & Instance()
  {
    static T inst;
    return inst;
  }

protected:
  Singleton() = default;
  ~Singleton() = default;

  Singleton(Singleton const &) = delete;
  Singleton(Singleton &&) = delete;

  Singleton & operator = (Singleton const &) = delete;
  Singleton & operator = (Singleton &&) = delete;

  void * operator new(std::size_t) = delete;
  void * operator new[](std::size_t) = delete;

  void operator delete(void *) = delete;
  void operator delete[](void *) = delete;

};
