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

Bullet & Bullet::operator = (Bullet const & obj)
{
  if (this == &obj) return *this;
  m_position = obj.GetPosition();
  m_size = obj.GetSize();
  m_speed = obj.GetSpeed();
  m_direction = obj.GetDirection();
  return *this;
}

bool Bullet::operator == (Bullet const & obj) const
{
  return m_position == obj.m_position &&
         m_size == obj.m_size &&
         m_speed == obj.m_speed &&
         m_direction == obj.m_direction;
}

void Bullet::Update()
{
  m_position += QVector2D(m_speed * m_direction.x(), m_speed * m_direction.y());
}

Shooter const & Bullet::GetShooter() const { return m_shooter; }
void Bullet::SetShooter(Shooter const & shooter) { m_shooter = shooter; }
