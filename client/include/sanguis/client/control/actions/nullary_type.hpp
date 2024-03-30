#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_NULLARY_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_NULLARY_TYPE_HPP_INCLUDED

#include <sanguis/client/control/actions/nullary_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::control::actions
{

enum class nullary_type : std::uint8_t
{
  change_world,
  console,
  drop_primary_weapon,
  drop_secondary_weapon,
  escape,
  perk_menu,
  reload_primary_weapon,
  // TODO(philipp): This is not needed anymore
  reload_secondary_weapon
};

}

#endif
