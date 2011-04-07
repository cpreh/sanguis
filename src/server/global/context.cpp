#include "context.hpp"
#include "world_context.hpp"
#include "load_context.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/speed.hpp"
#include "../entities/player.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/property/current_to_max.hpp"
#include "../world/object.hpp"
#include "../world/random.hpp"
#include "../perks/create.hpp"
#include "../perks/perk.hpp"
#include "../weapons/weapon.hpp"
#include "../create_player.hpp"
#include "../cheat.hpp"
#include "../send_available_perks.hpp"
#include "../log.hpp"
#include "../console.hpp"
#include "../../messages/remove_id.hpp"
#include "../../messages/connect_state.hpp"
#include "../../messages/create.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/to_angle.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

#include "../entities/insert_parameters.hpp"
#include "../entities/insert_parameters_center.hpp"
#include "../entities/pickups/weapon.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::global::context::context(
	server::unicast_callback const &_send_unicast,
	load::context_base const &_model_context,
	server::console &_console
)
:
	send_unicast_(_send_unicast),
	world_context_(
		fcppt::make_unique_ptr<
			global::world_context
		>(
			fcppt::ref(
				*this
			)
		)
	),
	load_context_(
		fcppt::make_unique_ptr<
			load_context
		>(
			_model_context
		)
	),
	console_(
		_console
	),
	players_(),
	worlds_()
{
}

sanguis::server::global::context::~context()
{
}

void
sanguis::server::global::context::insert_player(
	world_id const _world_id,
	player_id const _player_id,
	string const &_name,
	connect_state::type const _connect_state
)
{
	// send this before the world gets created
	send_unicast_(
		_player_id,
		messages::create(
			messages::connect_state(
				_connect_state
			)
		)
	);

	entities::player_unique_ptr player(
		server::create_player(
			*load_context_,
			_name,
			send_unicast_,
			_player_id,
			console_.known_commands()
		)
	);

	// currently, this may send console commands
	server::world::object &cur_world(
		this->world(
			_world_id
		)	
	);

	players_.insert(
		_player_id,
		player.get()
	);

	// FIXME: where to insert the player?
	server::center const spawn_pos(
		server::vector::null()
	);

	cur_world.insert(
		entities::unique_ptr(
			move(
				player
			)
		),
		entities::insert_parameters(
			spawn_pos,
			server::angle(
				0
			)
		)
	);

#if 0
	cur_world.insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::weapon
			>(
				fcppt::ref(
					*load_context_
				),
				team::players,
				weapon_type::pistol
			)
		),
		entities::insert_parameters_center(
			spawn_pos
		)
	);
#endif
}

void
sanguis::server::global::context::player_disconnect(
	player_id const _player_id
)
{
	players_[
		_player_id
	]->kill();
}

void
sanguis::server::global::context::player_target(
	player_id const _player_id,
	server::vector const &_target
)
{
	players_[
		_player_id
	]->target(
		_target
	);
}

void
sanguis::server::global::context::player_change_weapon(
	player_id const _player_id,
	weapon_type::type const _weapon
)
{
	players_[
		_player_id
	]->change_weapon(
		_weapon
	);
}

void
sanguis::server::global::context::player_angle(
	player_id const _player_id,
	server::angle const _angle
)
{
	entities::player &player(
		*players_[
			_player_id
		]
	);

	player.angle(
		_angle
	);

	send_unicast_(
		_player_id,
		message_convert::rotate(
			player
		)
	);
}

void
sanguis::server::global::context::player_change_shooting(
	player_id const _player_id,
	bool const _shooting
)
{
	players_[
		_player_id
	]->aggressive(
		_shooting
	);
}

void
sanguis::server::global::context::player_speed(
	player_id const _player_id,
	server::speed const &_speed
)
{
	entities::player &player(
		*players_[
			_player_id
		]
	);

	if(
		fcppt::math::vector::is_null(
			_speed.get()
		)
	)
		player.movement_speed().current(
			static_cast<
				space_unit
			>(
				0
			)
		);
	else
	{
		player.direction(
			server::direction(
				*fcppt::math::vector::to_angle<
					server::space_unit
				>(
					_speed.get()
				)
			)
		);
		
		entities::property::current_to_max(
			player.movement_speed()
		);
	}

	send_unicast_(
		_player_id,
		message_convert::speed(
			player
		)
	);
}

void
sanguis::server::global::context::player_cheat(
	player_id const _player_id,
	cheat_type::type const _cheat
)
{
	server::cheat(
		*players_[
			_player_id
		],
		_cheat
	);
}

void
sanguis::server::global::context::player_choose_perk(
	player_id const _player_id,
	perk_type::type const _perk_type
)
{
	entities::player &player(
		*players_[
			_player_id
		]
	);
	
	if(
		!player.perk_choosable(
			_perk_type
		)
	)
	{
		FCPPT_LOG_WARNING(
			context::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Player with id ")
				<< _player_id
				<< FCPPT_TEXT(" tried to take an invalid perk")
				<< FCPPT_TEXT(" or has no skillpoints left!")
		);

		return;
	}

	player.add_perk(
		perks::create(
			_perk_type
		)
	);
	
	server::send_available_perks(
		player,
		send_unicast_
	);
}

void
sanguis::server::global::context::update(
	time_type const _delta
)
{
	BOOST_FOREACH(
		server::world::map::reference cur_world,
		worlds_
	)
		cur_world.second->update(
			_delta
		);
}

sanguis::server::entities::player_map::size_type
sanguis::server::global::context::player_count() const
{
	return players_.size();
}

void
sanguis::server::global::context::send_to_player(
	player_id const _player_id,
	messages::auto_ptr _msg
)
{
	// TODO: we probably want to map this id to a net::id_type
	send_unicast_(
		_player_id,
		_msg
	);
}

void
sanguis::server::global::context::remove_player(
	player_id const _id
)
{
	send_unicast_(
		_id,
		messages::create(
			messages::remove_id()
		)
	);

	players_.erase(
		_id
	);
}

void
sanguis::server::global::context::transfer_entity(
	world_id const _destination,
	entities::unique_ptr _entity,
	entities::insert_parameters const &_insert_parameters
)
{
	this->world(
		_destination
	).insert(
		move(
			_entity
		),
		_insert_parameters
	);
}

sanguis::server::world::object &
sanguis::server::global::context::world(
	world_id const _world_id
)
{
	server::world::map::iterator const it(
		worlds_.find(
			_world_id
		)
	);

	if(
		it != worlds_.end()
	)
		return *it->second;
	
	return
		*fcppt::container::ptr::insert_unique_ptr_map(
			worlds_,
			_world_id,
			server::world::random(
				*world_context_,
				*load_context_,
				console_
			)
		).first->second;
}

fcppt::log::object &
sanguis::server::global::context::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("global::context")
		)
	);

	return my_logger;
}
