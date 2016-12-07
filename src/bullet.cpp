#include "bullet.hpp"

Bullet::Bullet(QVector2D position, QVector2D direction)
{
  m_position = std::move(position);
  m_direction = std::move(direction);
}

Bullet::Bullet(Bullet const & obj)
{
  m_position = obj.m_position;
  m_size = obj.m_size;
  m_speed = obj.m_speed;
  m_direction = obj.m_direction;
}

Bullet::Bullet(Bullet && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  std::swap(m_speed, obj.m_speed);
  std::swap(m_direction, obj.m_direction);
}

Bullet & Bullet::operator = (Bullet && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  std::swap(m_speed, obj.m_speed);
  std::swap(m_direction, obj.m_direction);
  return *this;
}
