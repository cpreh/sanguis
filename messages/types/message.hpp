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
enum type {
	add,
	add_decoration,
	add_enemy,
	add_pickup,
	add_projectile,
	add_weapon_pickup,
	assign_id,
	available_perks,
	change_weapon,
	client_info,
	connect,
	disconnect,
	experience,
	give_weapon,
	health,
	level_up,
	max_health,
	move,
	net_error,
	pause,
	player_change_weapon,
	player_choose_perk,
	player_direction,
	player_pause,
	player_rotation,
	player_start_shooting,
	player_stop_shooting,
	player_unpause,
	remove,
	resize,
	rotate,
	speed,
	start_attacking,
	stop_attacking,
	start_reloading,
	stop_reloading,
	unpause,
	size_
};
}

}
}
}

#endif
