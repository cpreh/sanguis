#ifndef SANGUIS_MESSAGES_SERVER_TYPES_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/server/types/message_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::messages::server::types
{

enum class message : std::uint8_t
{
  add_aoe_projectile,
  add_aura,
  add_buff,
  add_console_command,
  add_destructible,
  add_doodad,
  add_enemy,
  add_friend,
  add_own_player,
  add_pickup,
  add_player,
  add_projectile,
  add_weapon_pickup,
  available_perks,
  change_weapon,
  change_world,
  connected,
  console_print,
  die,
  experience,
  give_weapon,
  health,
  level_up,
  magazine_remaining,
  max_health,
  move,
  pause,
  reload,
  remove,
  remove_buff,
  remove_id,
  remove_weapon,
  rotate,
  slowdown,
  speed,
  unpause,
  weapon_status
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::messages::server::types::message::weapon_status);

#endif
