#ifndef SANGUIS_CREATOR_ENEMY_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_ENEMY_TYPE_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>

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
  reaper
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::creator::enemy_type::reaper);

#endif
