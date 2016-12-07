#pragma once

#include "gameentity.hpp"
#include "gun.hpp"
#include <list>
#include <vector>
#include <iostream>
#include <memory>

class Space
{
public:

  Space()
  {
    gun = new Gun();
    gun->SetSpeed(2);

    gun->SetPosition(QVector2D(m_width / 2.0f, 64));
//    gun->SetPosition(QVector2D(m_width / 2.0f, gun->GetSize().rheight() / 2.0f));
  }

  ~Space()
  {
    delete gun ;
  }

  int const GetWidth() const;
  int const GetHeight() const;

protected:

  int m_width = 1024.0f;
  int m_height = 768.0f;

  Gun * gun = nullptr;
  //std::list<std::shared_ptr<Alien>> m_alien;
  //std::list<std::shared_ptr<Bullet>> m_bullet;
  //std::list<std::shared_ptr<Obstacle>> m_obstacle;
};
