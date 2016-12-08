#pragma once

#include "gun.hpp"
#include "alien.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"

#include <list>
#include <vector>
#include <iostream>
#include <memory>

class Space
{
public:

  Space()
  {
    gun = std::shared_ptr<Gun>(new Gun);
    gun->SetSpeed(10);
    gun->SetSize(QSize(128, 64));
    gun->SetPosition(QVector2D(m_width / 2.0f, gun->GetSize().height() / 2.0f));

    for(int i = 0; i < m_amountAlien; i++)
    {
      m_alien.push_back(std::move(std::shared_ptr<Alien>(new Alien)));
      m_alien.back()->SetPosition(QVector2D(200*i + 100, 600));
    }

    for(int i = 0; i < m_amountObstacle; i++)
    {
      m_obstacle.push_back(std::move(std::shared_ptr<Obstacle>(new Obstacle)));
      m_obstacle.back()->SetPosition(QVector2D(200*i + 100, 300));
    }

  }

  ~Space()
  {}

  int const GetWidth() const;
  int const GetHeight() const;

protected:

  int m_width = 1024.0f;
  int m_height = 768.0f;
  int m_amountAlien = 5;
  int m_amountObstacle = 5;

  std::shared_ptr<Gun> gun;
  std::vector<std::shared_ptr<Alien>> m_alien;
  //std::vector<std::shared_ptr<Bullet>> m_bullet;
  std::vector<std::shared_ptr<Obstacle>> m_obstacle;
};
