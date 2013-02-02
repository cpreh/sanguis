#include <sanguis/cheat_type.hpp>
#include <sanguis/connect_state.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_seed.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/load/server_context_fwd.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/connect_state.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/remove_id.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/create_player.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/player_map.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/global/load_context.hpp>
#include <sanguis/server/global/world_context.hpp>
#include <sanguis/server/message_convert/rotate.hpp>
#include <sanguis/server/message_convert/speed.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/random.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
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
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
	sanguis::server::unicast_callback const &_send_unicast,
	sanguis::load::server_context const &_model_context,
	sge::charconv::system &_charconv_system,
	sanguis::server::console &_console
)
:
	diff_clock_(),
	random_generator_(
		sanguis::random_seed()
	),
	send_unicast_(
		_send_unicast
	),
	world_context_(
		fcppt::make_unique_ptr<
			sanguis::server::global::world_context
		>(
			*this
		)
	),
	load_context_(
		fcppt::make_unique_ptr<
			sanguis::server::global::load_context
		>(
			_model_context
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
	sanguis::world_id const _world_id,
	sanguis::server::player_id const _player_id,
	sanguis::server::string const &_name,
	sanguis::connect_state const _connect_state
)
{
	// send this before the world gets created
	this->send_to_player(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::connect_state(
				static_cast<
					sanguis::messages::types::enum_
				>(
					_connect_state
				)
			)
		)
	);

	sanguis::server::entities::player_unique_ptr player(
		sanguis::server::create_player(
			diff_clock_,
			random_generator_,
			*load_context_,
			charconv_system_,
			_name,
			send_unicast_,
			_player_id,
			console_.known_commands()
		)
	);

	// currently, this may send console commands
	sanguis::server::world::object &cur_world(
		this->world(
			_world_id
		)
	);

	players_.insert(
		_player_id,
		player.get()
	);

	// FIXME: where to insert the player?
	sanguis::server::center const spawn_pos(
		sanguis::server::vector::null()
	);

	sanguis::server::entities::player &player_ref(
		*player
	);

	cur_world.insert(
		std::move(
			player
		),
		sanguis::server::entities::insert_parameters(
			spawn_pos,
			sanguis::server::angle(
				0.f
			)
		)
	);

	cur_world.insert(
		fcppt::make_unique_ptr<
			sanguis::server::entities::pickups::weapon
		>(
			diff_clock_,
			random_generator_,
			*load_context_,
			sanguis::server::team::players,
			sanguis::weapon_type::pistol
		),
		sanguis::server::entities::insert_parameters_center(
			spawn_pos
		)
	);

	// send this after the player has been created
	sanguis::server::send_available_perks(
		player_ref,
		send_unicast_
	);
}

void
sanguis::server::global::context::player_disconnect(
	sanguis::server::player_id const _player_id
)
{
	players_[
		_player_id
	]->kill();
}

void
sanguis::server::global::context::player_target(
	sanguis::server::player_id const _player_id,
	sanguis::server::vector const &_target
)
{
	// handles rotation as well
	sanguis::server::entities::player &player(
		*players_[
			_player_id
		]
	);

	player.target(
		_target
	);

	sanguis::server::vector const player_center(
		player.center().get()
	);

	if(
		player_center
		== _target
	)
		return;

	player.angle(
		sanguis::server::angle(
			fcppt::math::vector::signed_angle_between(
				player_center,
				_target
			)
		)
	);

	this->send_to_player(
		_player_id,
		*sanguis::server::message_convert::rotate(
			player
		)
	);
}

void
sanguis::server::global::context::player_change_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::weapon_type const _weapon
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
	sanguis::server::player_id const _player_id,
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
	sanguis::server::player_id const _player_id,
	sanguis::server::speed const &_speed
)
{
	sanguis::server::entities::player &player(
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
			sanguis::server::space_unit
		>(
			0.0001f
		)
	)
		player.movement_speed().current(
			static_cast<
				sanguis::server::space_unit
			>(
				0
			)
		);
	else
	{
		player.direction(
			sanguis::server::direction(
				fcppt::math::vector::atan2(
					_speed.get()
				)
			)
		);

		// FIXME: don't set the speed to max!
		sanguis::server::entities::property::current_to_max(
			player.movement_speed()
		);
	}

	this->send_to_player(
		_player_id,
		*sanguis::server::message_convert::speed(
			player
		)
	);
}

void
sanguis::server::global::context::player_cheat(
	sanguis::server::player_id const _player_id,
	sanguis::cheat_type const _cheat
)
{
	sanguis::server::cheat(
		diff_clock_,
		random_generator_,
		*players_[
			_player_id
		],
		_cheat
	);
}

void
sanguis::server::global::context::player_choose_perk(
	sanguis::server::player_id const _player_id,
	sanguis::perk_type const _perk_type
)
{
	sanguis::server::entities::player &player(
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
		sanguis::server::perks::create(
			diff_clock_,
			random_generator_,
			_perk_type
		)
	);

	sanguis::server::send_available_perks(
		player,
		send_unicast_
	);
}

void
sanguis::server::global::context::update(
	sanguis::duration const &_diff
)
{
	sanguis::update_diff_clock(
		diff_clock_,
		_diff
	);

	for(
		auto world : worlds_
	)
		world.second->update();
}

sanguis::server::entities::player_map::size_type
sanguis::server::global::context::player_count() const
{
	return players_.size();
}

bool
sanguis::server::global::context::has_player(
	sanguis::server::player_id const _player_id
) const
{
	return
		players_.contains(
			_player_id
		);
}

void
sanguis::server::global::context::send_to_player(
	sanguis::server::player_id const _player_id,
	sanguis::messages::base const &_msg
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
	sanguis::server::player_id const _id
)
{
	this->send_to_player(
		_id,
		*sanguis::messages::create(
			sanguis::messages::remove_id()
		)
	);

	players_.erase(
		_id
	);
}

void
sanguis::server::global::context::transfer_entity(
	sanguis::world_id const _destination,
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	this->world(
		_destination
	).insert(
		std::move(
			_entity
		),
		_insert_parameters
	);
}

sanguis::server::world::object &
sanguis::server::global::context::world(
	sanguis::world_id const _world_id
)
{
	sanguis::server::world::map::iterator const it(
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
			sanguis::server::world::random(
				diff_clock_,
				random_generator_,
				*world_context_,
				*load_context_,
				charconv_system_,
				console_
			)
		).first->second;
}
