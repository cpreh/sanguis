#include "create_player.hpp"
#include "string.hpp"
#include "send_available_perks.hpp"
#include "damage/no_armor.hpp"
#include "damage/list.hpp"
#include "entities/player.hpp"
#include "entities/auto_ptr.hpp"
#include "weapons/weapon.hpp"
#include <fcppt/make_auto_ptr.hpp>

sanguis::server::entities::player_auto_ptr
sanguis::server::create_player(
	environment::load_context_ptr const load_context_,
	string const &name,
	unicast_callback const &send_to_player,
	player_id const player_id_,
	console_command_vector const &known_commands_
)
{
	entities::player_auto_ptr new_player(
		fcppt::make_auto_ptr<
			entities::player
		>(
			load_context_,
			entities::health_type(100),
			damage::no_armor(),
			entities::movement_speed(100),
			name,
			player_id_
		)
	);

	send_available_perks(
		*new_player,
		send_to_player
	);

	return new_player;
}
