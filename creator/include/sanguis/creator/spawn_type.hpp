#ifndef SANGUIS_CREATOR_SPAWN_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_SPAWN_TYPE_HPP_INCLUDED

#include <sanguis/creator/spawn_type_fwd.hpp>

namespace sanguis::creator
{

enum class spawn_type
{
  single,
  spawner,
  fcppt_maximum = spawner
};

}

#endif
