#pragma once

#include "destroyable.hpp"
#include <QVector2D>

class Obstacle : public Destroyable
{
public:
  Obstacle();
  Obstacle(QVector2D && position);
  Obstacle(Obstacle const & obj);
  Obstacle(Obstacle && obj);
  Obstacle & operator = (Obstacle && obj);
  Obstacle & operator = (Obstacle const & obj);
  bool operator == (Obstacle const & obj) const;

private:

};
