#ifndef SANGUIS_MESSAGES_TYPES_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_MESSAGE_HPP_INCLUDED

namespace sanguis
{
namespace messages
{
namespace types
{

namespace message
{
enum type
{
	add_aoe_projectile,
	add_console_command,
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
	client_info,
	connect_state,
	console_command,
	console_print,
	die,
	experience,
	give_weapon,
	health,
	level_up,
	max_health,
	move,
	pause,
	player_attack_dest,
	player_change_weapon,
	player_cheat,
	player_choose_perk,
	player_direction,
	player_pause,
	player_start_shooting,
	player_stop_shooting,
	player_unpause,
	remove,
	remove_id,
	rotate,
	speed,
	start_attacking,
	stop_attacking,
	start_reloading,
	stop_reloading,
	unpause,
	size
};
}

}
}
}

#endif