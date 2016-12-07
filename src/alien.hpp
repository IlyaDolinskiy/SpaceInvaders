#pragma once

#include "shootable.hpp"

class Alien : public Shootable
{
public:
  Alien() = default;
  Alien(QVector2D && position);

  Alien(Alien const & obj);
  Alien(Alien && obj);

  Alien & operator = (Alien && obj);
  Alien & operator = (Alien const & obj);
  bool operator == (Alien const & obj) const;

private:

};
