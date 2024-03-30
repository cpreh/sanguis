#ifndef SANGUIS_CREATOR_SPAWN_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_SPAWN_TYPE_HPP_INCLUDED

#include <sanguis/creator/spawn_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::creator
{

enum class spawn_type : std::uint8_t
{
  single,
  spawner,
  fcppt_maximum = spawner
};

}

#endif
