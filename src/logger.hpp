#pragma once

#include <iostream>
#include <utility>
#include <memory>
#include <ostream>
#include <sstream>
#include <fstream>

#include "space.hpp"
#include "singleton.hpp"

std::string const LOG_CREATE = "Create Object: ";
std::string const LOG_DAMAGE = "Damage Object: ";
std::string const LOG_DESTRUCTION = "Destruction Object: ";

std::string const LOG_ALIEN = "Alien\n";
std::string const LOG_GUN = "Gun\n";
std::string const LOG_OBSTACLE = "Obstacle\n";

class Logger : public Singleton<Logger>
{

public:
  template<typename T>
  Logger & operator << (T const & object);

  template<typename T, template<typename, typename...> class C, typename... Args>
  Logger & operator << (C<T, Args...> const & objs);

  Logger & operator << (std::string const & str);
  
private:
  Logger() = default;

  std::string os;

  void SaveToFile(std::string str);

  friend class Singleton<Logger>;

};

#define Log Singleton<Logger>::Instance()
