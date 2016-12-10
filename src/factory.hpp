#pragma once
#include <iostream>
#include <memory>
#include "singleton.hpp"

class Factory : public Singleton<Factory>
{
public:
  template<typename T, typename... Args>
  std::shared_ptr<T> Create(Args && ... args)
  {
    return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
  }

private:
  Factory() = default;
  friend class Singleton<Factory>;
};

#define factory Singleton<Factory>::Instance()
