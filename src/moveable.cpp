#include "moveable.hpp"

void Moveable::Move(float elapsedSeconds)
{
  m_position += QVector2D(m_speed*elapsedSeconds*m_direction.x(), m_speed*elapsedSeconds*m_direction.y());
}

float const & Moveable::GetSpeed() const { return m_speed; }
QVector2D const & Moveable::GetDirection() const { return m_direction; }

void Moveable::SetSpeed(float const & speed) { m_speed = speed; }
void Moveable::SetDirection(QVector2D && direction) { m_direction = std::move(direction); }
