#pragma once

#include "gameentity.hpp"
#include <QVector2D>

class Moveable : public GameEntity
{
public:
  void Move(float elapsedSeconds);

  float const & GetSpeed() const;
  QVector2D const & GetDirection() const;

  void SetSpeed(float const & speed);
  void SetDirection(QVector2D && direction);

protected:
  float m_speed = 1.0f;
  QVector2D m_direction = QVector2D(0.0f, 1.0f);
};
