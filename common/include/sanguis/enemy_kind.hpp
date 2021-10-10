#ifndef SANGUIS_ENEMY_KIND_HPP_INCLUDED
#define SANGUIS_ENEMY_KIND_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>

namespace sanguis
{

enum class enemy_kind
{
  normal,
  champion,
  unique,
  boss,
  fcppt_maximum = boss
};

}

#endif
