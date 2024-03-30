#ifndef SANGUIS_CREATOR_ENEMY_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_ENEMY_TYPE_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis::creator
{

// NOLINTNEXTLINE(performance-enum-size)
enum class enemy_type
{
  wolf_black,
  wolf_brown,
  wolf_white,
  zombie00,
  zombie01,
  spider,
  skeleton,
  ghost,
  maggot,
  reaper,
  fcppt_maximum = reaper
};

}

#endif
