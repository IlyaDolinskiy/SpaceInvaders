#include "shootable.hpp"

Bullet Shootable::Shot()
{

}

unsigned int const & Shootable::GetAmmo() const { return m_ammo; }
QVector2D const & Shootable::GetShotDirection() const { return m_shotDirection; }

void Shootable::SetAmmo(unsigned int const & ammo) { m_ammo = ammo; }
void Shootable::SetShotDirection(QVector2D && shotDirection) { m_shotDirection = std::move(shotDirection); }
