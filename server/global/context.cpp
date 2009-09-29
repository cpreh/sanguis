#include "context.hpp"
#include "world_context.hpp"
#include "load_context.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/speed.hpp"
#include "../entities/player.hpp"
#include "../entities/auto_ptr.hpp"
#include "../world/object.hpp"
#include "../world/random.hpp"
#include "../perks/factory.hpp"
#include "../weapons/weapon.hpp"
#include "../create_player.hpp"
#include "../cheat.hpp"
#include "../send_available_perks.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/to_angle.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <tr1/functional>

#include "../entities/insert_parameters.hpp"

sanguis::server::global::context::context(
	unicast_callback const &send_unicast_,
	sge::collision::system_ptr const collision_system_,
	load::model::context const &model_context_
)
:
	send_unicast_(send_unicast_),
	collision_system_(collision_system_),
	worlds_(),
	players_(),
	world_context_(
		sge::make_shared_ptr<
			world_context
		>(
			std::tr1::ref(
				*this
			)
		)
	),
	load_context_(
		sge::make_shared_ptr<
			load_context
		>(
			model_context_
		)
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

	entities::player_auto_ptr player_(
		create_player(
			load_context_,
			name,
			send_unicast_,
			connect_state_,
			player_id_
		)
	);

	players_.insert(
		player_id_,
		player_.get()
	);

	world_.insert(
		entities::auto_ptr(
			player_
		),
		// FIXME: where to insert the player?
		entities::insert_parameters(
			pos_type::null(),
			0
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
			*sge::math::vector::to_angle<space_unit>(dir)
		);
		
		player_.movement_speed().current_to_max();
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
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("Player with id ")
				<< player_id_
				<< SGE_TEXT(" tried to take an invalid perk")
				<< SGE_TEXT(" or has no skillpoints left!"));
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

sge::log::logger &
sanguis::server::global::context::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("global::context: "),
		true
	);

	return log_;
}
