#ifndef SANGUIS_CHEAT_TYPE_HPP_INCLUDED
#define SANGUIS_CHEAT_TYPE_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class cheat_type : std::uint8_t
{
  auras,
  exp,
  grenade,
  heal,
  kill,
  monster_spawner,
  perks,
  rocket_launcher,
  sentry,
  shotgun,
  spider
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::cheat_type::spider);

#endif
