#pragma once

#include "gun.hpp"
#include "alien.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"

#include <vector>
#include <memory>

#include <ctime>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

class Space
{
public:
  Space();
  int const GetWidth() const;
  int const GetHeight() const;

protected:
  int m_width = 512;
  int m_height = 600;

  int m_amountAlien = 5;
  int m_amountObstacle = 3;

  std::shared_ptr<Gun> m_gun;
  std::vector<std::shared_ptr<Alien>> m_alien;
  std::vector<std::shared_ptr<Bullet>> m_bullet;
  std::vector<std::shared_ptr<Obstacle>> m_obstacle;
};


class Random
{
public:
  static int const Int(int x, int y)
  {
    std::random_device rseed;
    std::mt19937 rgen(rseed());
    return static_cast<int>(std::uniform_int_distribution<int>(x,y)(rgen));
  }
};
