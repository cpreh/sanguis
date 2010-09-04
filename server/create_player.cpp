#include "create_player.hpp"
#include "string.hpp"
#include "send_available_perks.hpp"
#include "damage/no_armor.hpp"
#include "damage/list.hpp"
#include "entities/player.hpp"
#include "entities/unique_ptr.hpp"
#include "weapons/weapon.hpp"
#include "../messages/create.hpp"
#include "../messages/add_console_command.hpp"
#include <fcppt/utf8/convert.hpp>
#include <fcppt/homogenous_pair_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::player_unique_ptr
sanguis::server::create_player(
	environment::load_context_ptr const load_context_,
	string const &name,
	unicast_callback const &send_to_player,
	player_id const player_id_,
	console_command_vector const &known_commands_
)
{
	entities::player_unique_ptr new_player(
		fcppt::make_unique_ptr<
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

	BOOST_FOREACH(
		console_command_vector::const_reference elem,
		known_commands_
	)
		send_to_player(
			new_player->player_id(),
			messages::create(
				messages::add_console_command(
					fcppt::utf8::convert(
						elem.first
					),
					fcppt::utf8::convert(
						elem.second
					)
				)
			)
		);

	return
		move(
			new_player
		);
}
