#pragma once

#include <QVector2D>
#include <QSize>
#include <iostream>

class GameEntity
{
public:
  GameEntity() = default;
  GameEntity(QVector2D && position, QSize && size);
  GameEntity(QVector2D && position);
  GameEntity(GameEntity const & obj);
  GameEntity(GameEntity && obj);
  GameEntity & operator = (GameEntity && obj);

  QVector2D const & GetPosition() const;
  QSize const & GetSize() const;
  bool GetIsActive();

  void SetPosition(QVector2D && position);
  void SetSize(QSize && size);
  void SetIsActive(bool active);

  bool Intersection(GameEntity const & obj);

protected:
  QVector2D m_position = QVector2D(64, 64);
  QSize m_size = QSize(128, 128);

  bool m_isActive = true;

  QVector2D Vertex1() const;
  QVector2D Vertex3() const;

};
