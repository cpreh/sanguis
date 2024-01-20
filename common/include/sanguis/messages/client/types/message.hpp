#ifndef SANGUIS_MESSAGES_CLIENT_TYPES_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_TYPES_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/client/types/message_fwd.hpp> // IWYU pragma: keep

namespace sanguis::messages::client::types
{

enum class message
{
  attack_dest,
  change_world,
  cheat,
  choose_perk,
  console_command,
  direction,
  drop_or_pickup_weapon,
  info,
  pause,
  reload,
  start_shooting,
  stop_shooting,
  unpause,
  fcppt_maximum = unpause
};

}

#endif
