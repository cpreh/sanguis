#include "create_player.hpp"
#include "string.hpp"
#include "send_available_perks.hpp"
#include "damage_types.hpp"
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
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::player *
sanguis::server::create_player(
	messages::client_info const &client_info,
	send_callback const &send_to_player,
	environment const &env,
	entities::container const &entities,
	connect_state::type const current_state)
{
	string const &name(
		sge::utf8::convert(
			client_info.get<messages::string>()
		)
	);

	// TODO: this should be cleaned up somehow
	// 1) create the player
	// 2) tell the client the player's id _before_ doing anything else
	// 3) add the player
	entities::auto_ptr new_player(
		new entities::player(
			env,
			damage::list(static_cast<space_unit>(0)),
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
			name
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

	entities::player &p(
		dynamic_cast<entities::player &>(
			env.insert()(
				new_player
			)
		)
	);

	// TODO: some defaults here
	p.add_weapon(
		weapons::create(
			weapon_type::pistol,
			env
		)
	);

	send_to_player(
		message_convert::experience(p)
	);

	send_to_player(
		message_convert::level_up(p)
	);
	
	send_available_perks(
		p,
		send_to_player
	);

	BOOST_FOREACH(
		entities::entity const &e,
		entities
	)
	{
		if (e.id() == p.id())
			continue;

		send_to_player(
			e.add_message()
		);
	}

	return &p;
}
