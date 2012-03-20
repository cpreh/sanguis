#include <sanguis/server/global/context.hpp>
#include <sanguis/server/global/world_context.hpp>
#include <sanguis/server/global/load_context.hpp>
#include <sanguis/server/message_convert/rotate.hpp>
#include <sanguis/server/message_convert/speed.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/random.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/create_player.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/connect_state.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/remove_id.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/random_seed.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/vector/atan2.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/signed_angle_between.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <fcppt/math/dim/object_impl.hpp>

namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::log_location()
		/
		FCPPT_TEXT("global")
		/
		FCPPT_TEXT("context")
	)
);

}

sanguis::server::global::context::context(
	server::unicast_callback const &_send_unicast,
	load::context_base const &_model_context,
	sge::charconv::system &_charconv_system,
	server::console &_console
)
:
	diff_clock_(),
	random_generator_(
		sanguis::random_seed()
	),
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
			fcppt::cref(
				_model_context
			)
		)
	),
	charconv_system_(
		_charconv_system
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
	this->send_to_player(
		_player_id,
		*messages::create(
			messages::connect_state(
				_connect_state
			)
		)
	);

	entities::player_unique_ptr player(
		server::create_player(
			diff_clock_,
			*load_context_,
			charconv_system_,
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

	entities::player &player_ref(
		*player
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
				0.f
			)
		)
	);

	cur_world.insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::weapon
			>(
				fcppt::cref(
					diff_clock_
				),
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

	// send this after the player has been created
	server::send_available_perks(
		player_ref,
		send_unicast_
	);
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
	// handles rotation as well
	entities::player &player(
		*players_[
			_player_id
		]
	);

	player.target(
		_target
	);

	server::vector const player_center(
		player.center().get()
	);

	if(
		player_center
		== _target
	)
		return;

	player.angle(
		server::angle(
			fcppt::math::vector::signed_angle_between(
				player_center,
				_target
			)
		)
	);

	this->send_to_player(
		_player_id,
		*message_convert::rotate(
			player
		)
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
		fcppt::math::vector::length(
			_speed.get()
		)
		<
		static_cast<
			server::space_unit
		>(
			0.0001f
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
		// FIXME: don't set the speed to max!
		player.direction(
			server::direction(
				fcppt::math::vector::atan2(
					_speed.get()
				)
			)
		);

		entities::property::current_to_max(
			player.movement_speed()
		);
	}

	this->send_to_player(
		_player_id,
		*message_convert::speed(
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
		diff_clock_,
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
			::logger,
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
			diff_clock_,
			random_generator_,
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
	sanguis::duration const &_diff
)
{
	diff_clock_.update(
		_diff
	);

	for(
		server::world::map::iterator world_it(
			worlds_.begin()
		);
		world_it != worlds_.end();
		++world_it
	)
		world_it->second->update();
}

sanguis::server::entities::player_map::size_type
sanguis::server::global::context::player_count() const
{
	return players_.size();
}

void
sanguis::server::global::context::send_to_player(
	player_id const _player_id,
	messages::base const &_msg
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
	this->send_to_player(
		_id,
		*messages::create(
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
				diff_clock_,
				*world_context_,
				*load_context_,
				charconv_system_,
				console_
			)
		).first->second;
}
