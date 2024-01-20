#ifndef SANGUIS_ENEMY_KIND_HPP_INCLUDED
#define SANGUIS_ENEMY_KIND_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp> // IWYU pragma: keep

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
