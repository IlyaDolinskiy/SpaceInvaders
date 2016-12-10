#include "gameentity.hpp"

GameEntity::GameEntity(QVector2D && position, QSize && size)
  : m_position(std::move(position))
  , m_size(std::move(size))
{}

GameEntity::GameEntity(QVector2D && position)
  : m_position(std::move(position))
{}

GameEntity::GameEntity(GameEntity const & obj)
  : m_position(std::move(m_position))
  , m_size(std::move(m_size))
{}

GameEntity::GameEntity(GameEntity && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
}

GameEntity & GameEntity::operator = (GameEntity && obj)
{
  std::swap(m_position, obj.m_position);
  std::swap(m_size, obj.m_size);
  return *this;
}

QVector2D const & GameEntity::GetPosition() const { return m_position; }
QSize const & GameEntity::GetSize() const { return m_size; }
bool GameEntity::GetIsActive() { return m_isActive; }

void GameEntity::SetPosition(QVector2D && position) { m_position = std::move(position); }
void GameEntity::SetSize(QSize && size) { m_size = std::move(size);}
void GameEntity::SetIsActive(bool active) { m_isActive = active; }

bool GameEntity::Intersection(GameEntity const & obj)
{
  return !(Vertex3().y() <= obj.Vertex1().y() ||
           Vertex1().y() >= obj.Vertex3().y() ||
           Vertex3().x() <= obj.Vertex1().x() ||
           Vertex1().x() >= obj.Vertex3().x());
}

QVector2D GameEntity::Vertex1() const { return m_position + QVector2D(-m_size.width() / 2.0f, -m_size.height() / 2.0f); }
QVector2D GameEntity::Vertex3() const { return m_position + QVector2D(m_size.width() / 2.0f, m_size.height() / 2.0f); }
