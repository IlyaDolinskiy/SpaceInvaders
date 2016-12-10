#pragma once

#include "destroyable.hpp"
#include "bullet.hpp"
#include <QVector2D>
#include <memory>

class Shootable : public Destroyable
{
public:
  std::shared_ptr<Bullet> Shot(QVector2D && position, QVector2D && direction, Shooter shooter);

  unsigned int const & GetAmmo() const;
  QVector2D const & GetShotDirection() const;

  void SetAmmo(unsigned int const & ammo);
  void SetShotDirection(QVector2D && direction);

protected:
  unsigned int m_ammo = 100;
  QVector2D m_shotDirection = QVector2D(0.0f, 1.0f);
};
