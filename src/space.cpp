#include "space.hpp"

Space::Space()
{
  m_gun = std::shared_ptr<Gun>(new Gun);
  m_gun->SetSpeed(10);
  m_gun->SetSize(QSize(64, 32));
  m_gun->SetShotDirection(QVector2D(0, 1));
  m_gun->SetPosition(QVector2D(m_width / 2.0f, m_gun->GetSize().height() / 2.0f));

  for(int i = 0; i < m_amountAlien; i++)
  {
    m_alien.push_back(std::move(std::shared_ptr<Alien>(new Alien)));
    m_alien.back()->SetPosition(QVector2D(100*i + 50, 500));
    m_alien.back()->SetShotDirection(QVector2D(0, -1));
    m_alien.back()->SetSize(QSize(64, 64));
  }

  for(int i = 0; i < m_amountObstacle; i++)
  {
    m_obstacle.push_back(std::move(std::shared_ptr<Obstacle>(new Obstacle)));
    m_obstacle.back()->SetPosition(QVector2D(200*i + 60, 150));
    m_obstacle.back()->SetSize(QSize(100, 45));
  }

}

int const Space::GetWidth() const { return m_width; }
int const Space::GetHeight() const { return m_height; }
