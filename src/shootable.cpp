#include "shootable.hpp"

std::shared_ptr<Bullet> Shootable::Shot(QVector2D && position, QVector2D && direction)
{
  if (m_ammo > 0)
  {
    m_ammo--;
    std::shared_ptr<Bullet> bullet(new Bullet);
    bullet->SetPosition(std::move(position));
    bullet->SetDirection(std::move(direction));
    bullet->SetSize(QSize(5, 8));
    bullet->SetSpeed(20);
    return bullet;
  }
  else
  {

  }
}

unsigned int const & Shootable::GetAmmo() const { return m_ammo; }
QVector2D const & Shootable::GetShotDirection() const { return m_shotDirection; }

void Shootable::SetAmmo(unsigned int const & ammo) { m_ammo = ammo; }
void Shootable::SetShotDirection(QVector2D && shotDirection) { m_shotDirection = std::move(shotDirection); }
