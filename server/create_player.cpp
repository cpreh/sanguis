#include "create_player.hpp"
#include "string.hpp"
#include "send_available_perks.hpp"
#include "damage/no_armor.hpp"
#include "damage/list.hpp"
#include "entities/player.hpp"
#include "entities/auto_ptr.hpp"
#include "weapons/factory.hpp"
#include "weapons/weapon.hpp"
#include "message_convert/experience.hpp"
#include "message_convert/level_up.hpp"
#include "../messages/create.hpp"
#include "../messages/assign_id.hpp"
#include "../resolution.hpp"
#include <sge/utf8/convert.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::player *
sanguis::server::create_player(
	string const &name,
	send_callback const &send_to_player,
	environment const &env,
	connect_state::type const current_state,
	net::id_type const net_id
)
{
	
	// TODO: this should be cleaned up somehow
	// 1) create the player
	// 2) tell the client the player's id _before_ doing anything else
	// 3) add the player
	entities::player_auto_ptr new_player(
		sge::make_auto_ptr<
			entities::player
		>(
			env,
			damage::no_armor(),
			pos_type(
				static_cast<space_unit>(resolution().w()/2),
				static_cast<space_unit>(resolution().h()/2)
			),
			static_cast<space_unit>(0),
			static_cast<space_unit>(0),
			boost::assign::map_list_of
				(
					entities::property_type::health,
					entities::property(
						static_cast<space_unit>(100)
					)
				)
				(
					entities::property_type::movement_speed,
					entities::property(
						static_cast<space_unit>(0),
						static_cast<space_unit>(100)
					)
				),
			name,
			net_id
		)
	);

	send_to_player(
		messages::create(
			messages::assign_id(
				new_player->id(),
				current_state
			)
		)
	);

	// TODO: some defaults here
	new_player->add_weapon(
		weapons::create(
			weapon_type::pistol,
			env
		)
	);

	send_to_player(
		message_convert::experience(
			*new_player
		)
	);

	send_to_player(
		message_convert::level_up(
			*new_player
		)
	);
	
	send_available_perks(
		*new_player,
		send_to_player
	);

	return new_player;
}
