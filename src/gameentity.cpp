#include "gameentity.hpp"

GameEntity::GameEntity(QVector2D && position, QSize && size)
  : m_position(std::move(position))
  , m_size(std::move(size))
{
  RecalcVertices();
}

GameEntity::GameEntity(QVector2D && position)
  : m_position(std::move(position))
{
  RecalcVertices();
}

GameEntity::GameEntity(GameEntity const & obj)
  : m_position(std::move(m_position))
  , m_size(std::move(m_size))
{
  RecalcVertices();
}

GameEntity::GameEntity(GameEntity && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  RecalcVertices();
}

GameEntity & GameEntity::operator = (GameEntity && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  RecalcVertices();
  return *this;
}

QVector2D const & GameEntity::GetPosition() const { return m_position; }
QSize const & GameEntity::GetSize() const { return m_size; }
QVector2D const & GameEntity::GetVertex1() const { return m_vertex1; }
QVector2D const & GameEntity::GetVertex2() const { return m_vertex2; }
QVector2D const & GameEntity::GetVertex3() const { return m_vertex3; }
QVector2D const & GameEntity::GetVertex4() const { return m_vertex4; }

void GameEntity::SetPosition(QVector2D && position)
{
  m_position = std::move(position);
  RecalcVertices();
}
void GameEntity::SetSize(QSize && size)
{
  m_size = std::move(size);
  RecalcVertices();
}

bool GameEntity::Intersection(GameEntity const & obj1, GameEntity const & obj2)
{
  return !(obj1.m_vertex3.y() <= obj2.m_vertex1.y() ||
           obj1.m_vertex1.y() >= obj2.m_vertex3.y() ||
           obj1.m_vertex3.x() <= obj2.m_vertex1.x() ||
           obj1.m_vertex1.x() >= obj2.m_vertex3.x());
}

void GameEntity::RecalcVertices()
{
  m_vertex1 = m_position + QVector2D(-m_size.rwidth() / 2.0f, -m_size.rheight() / 2.0f);
  m_vertex2 = m_position + QVector2D(-m_size.rwidth() / 2.0f, m_size.rheight() / 2.0f);
  m_vertex3 = m_position + QVector2D(m_size.rwidth() / 2.0f, m_size.rheight() / 2.0f);
  m_vertex4 = m_position + QVector2D(m_size.rwidth() / 2.0f, -m_size.rheight() / 2.0f);
}
