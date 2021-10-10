#ifndef SANGUIS_CREATOR_ENEMY_KIND_HPP_INCLUDED
#define SANGUIS_CREATOR_ENEMY_KIND_HPP_INCLUDED

#include <sanguis/creator/enemy_kind_fwd.hpp>

namespace sanguis::creator
{

enum class enemy_kind
{
  normal,
  unique,
  boss,
  fcppt_maximum = boss
};

}

#endif
