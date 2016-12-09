#pragma once

#include "moveable.hpp"

enum class Shooter { Gun, Alien };

class Bullet : public Moveable
{
public:
  Bullet() = default;
  Bullet(QVector2D position, QVector2D direction);
  Bullet(Bullet const & obj);
  Bullet(Bullet && obj);
  Bullet & operator = (Bullet && obj);
  Bullet & operator = (Bullet const & obj);
  bool operator == (Bullet const & obj) const;

  void Update();
  Shooter const & GetShooter() const;
  void SetShooter(Shooter const & shooter);
private:  
  Shooter m_shooter = Shooter::Gun;
};
