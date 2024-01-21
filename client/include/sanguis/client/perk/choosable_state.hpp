#ifndef SANGUIS_CLIENT_PERK_CHOOSABLE_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHOOSABLE_STATE_HPP_INCLUDED

#include <sanguis/client/perk/choosable_state_fwd.hpp> // IWYU pragma: keep

namespace sanguis::client::perk
{

enum class choosable_state
{
  ok,
  parent_level,
  player_level,
  max_level,
  level_up
};

}

#endif
