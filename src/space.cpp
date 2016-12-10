#include "space.hpp"

Space::Space()
{
  std::ofstream f("log.txt", std::ios::trunc);
  if (f.is_open())
    f.close();
  else
  {
    Log << std::string("Error opening file\n");
    std::cerr << "Error opening file" << std::endl;
  }

  m_gun = factory.Create<Gun>();
  m_gun->SetSpeed(10);
  m_gun->SetSize(QSize(64, 32));
  m_gun->SetShotDirection(QVector2D(0, 1));
  m_gun->SetPosition(QVector2D(m_width / 2.0f, m_gun->GetSize().height() / 2.0f));
  Log << LOG_CREATE << LOG_GUN;

  for(int i = 0; i < m_amountAlien; i++)
  {
    m_alien.push_back(std::move(factory.Create<Alien>()));
    m_alien.back()->SetPosition(QVector2D(100*i + 50, 450));
    m_alien.back()->SetShotDirection(QVector2D(0, -1));
    m_alien.back()->SetSize(QSize(64, 64));
    m_alien.back()->SetAmmo(10000);
    Log << LOG_CREATE << LOG_ALIEN;
  }

  for(int i = 0; i < m_amountObstacle; i++)
  {
    m_obstacle.push_back(std::move(factory.Create<Obstacle>()));
    m_obstacle.back()->SetPosition(QVector2D(200*i + 60, 150));
    m_obstacle.back()->SetSize(QSize(100, 45));
    Log << LOG_CREATE << LOG_OBSTACLE;
  }
}

int const Space::GetWidth() const { return m_width; }
int const Space::GetHeight() const { return m_height; }
