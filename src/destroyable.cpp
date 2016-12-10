#include "destroyable.hpp"

void Destroyable::Damage()
{
  if (m_health - m_damage > 0)
    m_health -= m_damage;
  else
  {
    m_health = 0;
    m_isActive = false;
  }
}

float const & Destroyable::GetHealth() const { return m_health; }
float const & Destroyable::GetDamage() const { return m_damage; }

void Destroyable::SetHealth(float const & health) { m_health = health; }
void Destroyable::SetDamage(float const & damage) { m_damage = damage; }
