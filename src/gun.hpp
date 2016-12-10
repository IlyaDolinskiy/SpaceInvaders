#pragma once

#include "shootable.hpp"

class Gun : public Shootable
{
public:
  Gun() = default;
  Gun(QVector2D && position);
  Gun(Gun const & obj);
  Gun(Gun && obj);
  Gun & operator = (Gun && obj);
  Gun & operator = (Gun const & obj);
  bool operator == (Gun const & obj) const;

private:

};
