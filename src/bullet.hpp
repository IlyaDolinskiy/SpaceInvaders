#pragma once

#include "moveable.hpp"

class Bullet : public Moveable
{
public:
  Bullet() = default;
  Bullet(QVector2D position, QVector2D direction);
  Bullet(Bullet const & obj);
  Bullet(Bullet && obj);
  Bullet & operator = (Bullet && obj);

private:

};
