#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_NULLARY_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_NULLARY_TYPE_HPP_INCLUDED

#include <sanguis/client/control/actions/nullary_type_fwd.hpp>

namespace sanguis::client::control::actions
{

enum class nullary_type
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
