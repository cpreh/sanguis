#include "context.hpp"
#include "world_context.hpp"
#include "load_context.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/speed.hpp"
#include "../entities/player.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/property/current_to_max.hpp"
#include "../world/object.hpp"
#include "../world/random.hpp"
#include "../perks/factory.hpp"
#include "../weapons/weapon.hpp"
#include "../create_player.hpp"
#include "../cheat.hpp"
#include "../send_available_perks.hpp"
#include "../log.hpp"
#include "../../messages/remove_id.hpp"
#include "../../messages/connect_state.hpp"
#include "../../messages/create.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/to_angle.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

#include "../entities/insert_parameters.hpp"
#include "../entities/insert_parameters_pos.hpp"
#include "../entities/pickups/weapon.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::global::context::context(
	unicast_callback const &send_unicast_,
	sge::collision::system_ptr const collision_system_,
	load::context_base const &model_context_,
	sge::console::object &console_
)
:
	send_unicast_(send_unicast_),
	collision_system_(collision_system_),
	worlds_(),
	players_(),
	world_context_(
		fcppt::make_shared_ptr<
			world_context
		>(
			std::tr1::ref(
				*this
			)
		)
	),
	load_context_(
		fcppt::make_shared_ptr<
			load_context
		>(
			model_context_
		)
	),
	console_(
		console_
	)
{}

sanguis::server::global::context::~context()
{}

void
sanguis::server::global::context::insert_player(
	world_id const world_id_,
	player_id const player_id_,
	string const &name,
	connect_state::type const connect_state_
)
{
	server::world::object &world_(
		world(
			world_id_
		)	
	);

	send_unicast_(
		player_id_,
		messages::create(
			messages::connect_state(
				connect_state_
			)
		)
	);

	entities::player_auto_ptr player_(
		create_player(
			load_context_,
			name,
			send_unicast_,
			player_id_
		)
	);

	players_.insert(
		player_id_,
		player_.get()
	);

	// FIXME: where to insert the player?
	pos_type const spawn_pos(
		pos_type::null()
	);

	world_.insert(
		entities::auto_ptr(
			player_
		),
		entities::insert_parameters(
			spawn_pos,
			0
		)
	);

	world_.insert(
		entities::auto_ptr(
			new entities::pickups::weapon(
				load_context_,
				team::players,
				weapon_type::pistol
			)
		),
		entities::insert_parameters_pos(
			spawn_pos
		)
	);
}

void
sanguis::server::global::context::player_disconnect(
	player_id const player_id_
)
{
	players_[
		player_id_
	]->die();
}

void
sanguis::server::global::context::player_target(
	player_id const player_id_,
	pos_type const &target_
)
{
	players_[
		player_id_
	]->target(
		target_
	);
}

void
sanguis::server::global::context::player_change_weapon(
	player_id const player_id_,
	weapon_type::type const wt
)
{
	players_[
		player_id_
	]->change_weapon(
		wt
	);
}

void
sanguis::server::global::context::player_angle(
	player_id const player_id_,
	space_unit const angle_
)
{
	entities::player &player_(
		*players_[
			player_id_
		]
	);

	player_.angle(
		angle_
	);

	send_unicast_(
		player_id_,
		message_convert::rotate(
			player_
		)
	);
}

void
sanguis::server::global::context::player_change_shooting(
	player_id const player_id_,
	bool const shooting
)
{
	players_[
		player_id_
	]->aggressive(
		shooting
	);
}

void
sanguis::server::global::context::player_direction(
	player_id const player_id_,
	pos_type const &dir
)
{
	entities::player &player_(
		*players_[
			player_id_
		]
	);

	if (is_null(dir))
		player_.movement_speed().current(
			static_cast<space_unit>(0)
		);
	else
	{
		player_.direction(
			*fcppt::math::vector::to_angle<space_unit>(dir)
		);
		
		entities::property::current_to_max(
			player_.movement_speed()
		);
	}

	send_unicast_(
		player_id_,
		message_convert::speed(
			player_
		)
	);
}

void
sanguis::server::global::context::player_cheat(
	player_id const player_id_,
	cheat_type::type const cheat_
)
{
	server::cheat(
		*players_[
			player_id_
		],
		cheat_
	);
}

void
sanguis::server::global::context::player_choose_perk(
	player_id const player_id_,
	perk_type::type const perk_type_
)
{
	entities::player &player_(
		*players_[
			player_id_
		]
	);
	
	if(
		!player_.perk_choosable(
			perk_type_
		)
	)
	{
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Player with id ")
				<< player_id_
				<< FCPPT_TEXT(" tried to take an invalid perk")
				<< FCPPT_TEXT(" or has no skillpoints left!"));
		return;
	}

	player_.add_perk(
		perks::create(
			perk_type_
		)
	);
	
	send_available_perks(
		player_,
		send_unicast_
	);
}

void
sanguis::server::global::context::update(
	time_type const delta
)
{
	BOOST_FOREACH(
		server::world::map::reference world_,
		worlds_
	)
		world_.second->update(
			delta
		);
}

void
sanguis::server::global::context::send_to_player(
	player_id const player_id_,
	messages::auto_ptr msg_
)
{
	// TODO: we probably want to map this id to a net::id_type
	send_unicast_(
		player_id_,
		msg_
	);
}

void
sanguis::server::global::context::remove_player(
	player_id const id_
)
{
	send_unicast_(
		id_,
		messages::create(
			messages::remove_id()
		)
	);

	players_.erase(
		id_
	);
}

void
sanguis::server::global::context::transfer_entity(
	world_id const destination,
	entities::auto_ptr entity,
	entities::insert_parameters const &insert_parameters_
)
{
	world(
		destination
	).insert(
		entity,
		insert_parameters_
	);
}

sanguis::server::world::object &
sanguis::server::global::context::world(
	world_id const world_id_
)
{
	server::world::map::iterator const it(
		worlds_.find(
			world_id_	
		)
	);

	if(
		it != worlds_.end()
	)
		return *it->second;
	
	return *worlds_.insert(
		world_id_,
		server::world::random(
			world_context_,
			collision_system_,
			load_context_
		)
	).first->second;
}

fcppt::log::object &
sanguis::server::global::context::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("global::context")
		)
	);

	return log_;
}
