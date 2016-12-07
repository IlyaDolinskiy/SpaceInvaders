#include "obstacle.hpp"

Obstacle::Obstacle()
{
  m_speed = 0;
  m_direction = QVector2D(1, 0);
}

Obstacle::Obstacle(QVector2D && position)
{
  m_position = std::move(position);
  m_speed = 0;
  m_direction = QVector2D(1, 0);
}

Obstacle::Obstacle(Obstacle const & obj)
{
  m_position = obj.m_position;
  m_size = obj.m_size;
  m_speed = obj.m_speed;
  m_direction = obj.m_direction;
  m_health = obj.m_health;
  m_damage = obj.m_damage;
}

Obstacle::Obstacle(Obstacle && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  std::swap(m_speed, obj.m_speed);
  std::swap(m_direction, obj.m_direction);
  std::swap(m_health, obj.m_health);
  std::swap(m_damage, obj.m_damage);
}

Obstacle & Obstacle::operator = (Obstacle && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  std::swap(m_speed, obj.m_speed);
  std::swap(m_direction, obj.m_direction);
  std::swap(m_health, obj.m_health);
  std::swap(m_damage, obj.m_damage);
  return *this;
}

Obstacle & Obstacle::operator = (Obstacle const & obj)
{
  if (this == &obj) return *this;
  m_position = obj.GetPosition();
  m_size = obj.GetSize();
  m_speed = obj.GetSpeed();
  m_direction = obj.GetDirection();
  m_health = obj.GetHealth();
  m_damage = obj.GetDamage();
  return *this;
}

bool Obstacle::operator == (Obstacle const & obj) const
{
  return m_position == obj.m_position &&
         m_size == obj.m_size &&
         m_speed == obj.m_speed &&
         m_direction == obj.m_direction &&
         m_health == obj.m_health &&
         m_damage == obj.m_damage;
}
