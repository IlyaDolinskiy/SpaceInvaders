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
    gun->SetPosition(QVector2D(m_width / 2.0f, gun->GetSize().height() / 2.0f));

    for(int i = 0; i < m_amountAlien; i++)
    {
      m_alienArray.push_back(std::move(std::shared_ptr<Alien>(new Alien)));
      m_alienArray.back()->SetPosition(QVector2D(200*i + 100, 400));
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

  std::shared_ptr<Gun> gun;
  std::vector<std::shared_ptr<Alien>> m_alienArray;
  //std::vector<std::shared_ptr<Bullet>> m_bulletArray;
  //std::vector<std::shared_ptr<Obstacle>> m_obstacleArray;
};
