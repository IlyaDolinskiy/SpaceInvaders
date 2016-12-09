#pragma once

#include "moveable.hpp"

class Destroyable : public Moveable
{
public:
  void Damage();

  float const & GetHealth() const;
  float const & GetDamage() const;

  void SetHealth(float const & health);
  void SetDamage(float const & damage);

protected:
  float m_health = 5.0f;
  float m_damage = 1.0f;
};
