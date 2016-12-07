#pragma once

#include <QVector2D>
#include <QSize>

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
  QVector2D const & GetVertex1() const;
  QVector2D const & GetVertex2() const;
  QVector2D const & GetVertex3() const;
  QVector2D const & GetVertex4() const;

  void SetPosition(QVector2D && position);
  void SetSize(QSize && size);

  bool Intersection(GameEntity const & obj1, GameEntity const & obj2);

protected:
  QVector2D m_position = QVector2D(64, 64);
  QSize m_size = QSize(128, 128);

  QVector2D m_vertex1 = QVector2D(0, 0);      //vertex left bottom
  QVector2D m_vertex2 = QVector2D(0, 128);    //vertex left top
  QVector2D m_vertex3 = QVector2D(128, 128);  //vertex right top
  QVector2D m_vertex4 = QVector2D(128, 0);    //vertex right bottom

  void RecalcVertices();

};
