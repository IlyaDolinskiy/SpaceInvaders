#include "alien.hpp"
#include "shootable.hpp"

Alien::Alien(QVector2D && position)
{
  m_position = std::move(position);
}

Alien::Alien(Alien const & obj)

{
  m_position = obj.m_position;
  m_size = obj.m_size;
  m_speed = obj.m_speed;
  m_direction = obj.m_direction;
  m_health = obj.m_health;
  m_damage = obj.m_damage;
  m_ammo = obj.m_ammo;
  m_shotDirection = obj.m_shotDirection;

  RecalcVertices();
}

Alien::Alien(Alien && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  std::swap(m_speed, obj.m_speed);
  std::swap(m_direction, obj.m_direction);
  std::swap(m_health, obj.m_health);
  std::swap(m_damage, obj.m_damage);
  std::swap(m_ammo, obj.m_ammo);
  std::swap(m_shotDirection, obj.m_shotDirection);

  RecalcVertices();
}

Alien & Alien::operator = (Alien && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  std::swap(m_speed, obj.m_speed);
  std::swap(m_direction, obj.m_direction);
  std::swap(m_health, obj.m_health);
  std::swap(m_damage, obj.m_damage);
  std::swap(m_ammo, obj.m_ammo);
  std::swap(m_shotDirection, obj.m_shotDirection);
  return *this;
}

Alien & Alien::operator = (Alien const & obj)
{
  if (this == &obj) return *this;
  m_position = obj.GetPosition();
  m_size = obj.GetSize();
  m_speed = obj.GetSpeed();
  m_direction = obj.GetDirection();
  m_health = obj.GetHealth();
  m_damage = obj.GetDamage();
  m_ammo = obj.GetAmmo();
  m_shotDirection = obj.GetShotDirection();
  return *this;
}

bool Alien::operator == (Alien const & obj) const
{
  return m_position == obj.m_position &&
         m_size == obj.m_size &&
         m_speed == obj.m_speed &&
         m_direction == obj.m_direction &&
         m_health == obj.m_health &&
         m_damage == obj.m_damage &&
         m_ammo == obj.m_ammo &&
         m_shotDirection == obj.m_shotDirection;
}
