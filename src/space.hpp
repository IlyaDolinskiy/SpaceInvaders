#pragma once

#include "gun.hpp"
#include "alien.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "logger.hpp"
#include "factory.hpp"

#include <vector>
#include <memory>

enum class Status { Win, Lose };

class Space
{
public:
  Space();
  int const GetWidth() const;
  int const GetHeight() const;
  void GunCreate();
  void AlienCreate();
  void ObstacleCreate();
  void ClearLogFile();

protected:
  int m_width = 512;
  int m_height = 600;

  int m_amountAlien = 5;
  int m_amountObstacle = 3;

  bool m_gameIsActive = true;
  Status m_status = Status::Lose;

  int m_score = 0;

  std::shared_ptr<Gun> m_gun;
  std::vector<std::shared_ptr<Alien>> m_alien;
  std::vector<std::shared_ptr<Bullet>> m_bullet;
  std::vector<std::shared_ptr<Obstacle>> m_obstacle;
};

#include <ctime>

class Random
{
public:
  static int const Int(int min, int max)
  {
    srand(clock());
    return min + rand() % (max - min + 1);
  }
};
