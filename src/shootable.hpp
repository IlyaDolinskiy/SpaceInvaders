#pragma once

#include "destroyable.hpp"
#include "bullet.hpp"

class Shootable : public Destroyable
{
public:
  Bullet Shot();

  unsigned int const & GetAmmo() const;
  QVector2D const & GetShotDirection() const;

  void SetAmmo(unsigned int const & ammo);
  void SetShotDirection(QVector2D && direction);

protected:
  unsigned int m_ammo = 100;
  QVector2D m_shotDirection = QVector2D(0.0f, 1.0f);
};
