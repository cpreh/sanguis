#include <sanguis/cheat_type.hpp>
#include <sanguis/connect_state.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_seed.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/load/server_context_fwd.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/connect_state.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/remove_id.hpp>
#include <sanguis/messages/rotate.hpp>
#include <sanguis/messages/speed.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/create_player.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/insert_with_result.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/global/generate_worlds.hpp>
#include <sanguis/server/global/load_context.hpp>
#include <sanguis/server/global/next_id_callback.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/world_connection_map.hpp>
#include <sanguis/server/global/world_context.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/length_square.hpp>
#include <fcppt/math/vector/signed_angle_between.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
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
	sanguis::server::console &_console
)
:
	diff_clock_(),
	random_generator_(
		sanguis::random_seed()
	),
	next_id_(
		0u
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
			_model_context,
			sanguis::server::global::next_id_callback(
				std::bind(
					&sanguis::server::global::context::next_id,
					this
				)
			)
		)
	),
	console_(
		_console
	),
	players_(),
	worlds_(
		sanguis::server::global::generate_worlds(
			sanguis::server::world::parameters(
				diff_clock_,
				random_generator_,
				*world_context_,
				*load_context_
			)
		)
	)
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
				_connect_state
			)
		)
	);

	sanguis::server::entities::player_unique_ptr player_ptr(
		sanguis::server::create_player(
			diff_clock_,
			*load_context_,
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
		std::make_pair(
			_player_id,
			player_ptr.get()
		)
	);

	if(
		cur_world.openings().empty()
	)
	{
		FCPPT_LOG_ERROR(
			logger,
			fcppt::log::_
				<< FCPPT_TEXT("A world has no openings, so can't insert the player!")
		);

		return;
	}

	typedef fcppt::optional<
		sanguis::server::entities::player const &
	> const_optional_player_ref;

	const_optional_player_ref const player_ref(
		sanguis::server::entities::insert_with_result(
			cur_world,
			std::move(
				player_ptr
			),
			sanguis::server::entities::insert_parameters(
				sanguis::server::world::grid_pos_to_center(
					cur_world.openings()[
						0u
					].get()
				),
				sanguis::server::angle(
					0.f
				)
			)
		)
	);

	if(
		!player_ref.has_value()
	)
	{
		FCPPT_LOG_ERROR(
			logger,
			fcppt::log::_
				<< FCPPT_TEXT("Unable to insert a player!")
		);

		// TODO: What do we do here?
		return;
	}

	// send this after the player has been created
	sanguis::server::send_available_perks(
		*player_ref,
		send_unicast_
	);
}

void
sanguis::server::global::context::player_disconnect(
	sanguis::server::player_id const _player_id
)
{
	this->player(
		_player_id
	).kill();
}

void
sanguis::server::global::context::player_target(
	sanguis::server::player_id const _player_id,
	sanguis::server::vector const &_target
)
{
	// handles rotation as well
	sanguis::server::entities::player &player_ref(
		this->player(
			_player_id
		)
	);

	player_ref.target(
		sanguis::server::weapons::target(
			_target
		)
	);

	sanguis::server::vector const player_center(
		player_ref.center().get()
	);

	if(
		fcppt::math::vector::length_square(
			player_center
			-
			_target
		)
		< 1.f
	)
		return;

	player_ref.angle(
		sanguis::server::angle(
			fcppt::math::vector::signed_angle_between(
				player_center,
				_target
			)
		)
	);

	this->send_to_player(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::rotate(
				player_ref.id(),
				player_ref.angle().get()
			)
		)
	);
}

void
sanguis::server::global::context::player_change_world(
	sanguis::server::player_id const _player_id
)
{
	this->player(
		_player_id
	).transfer_from_world();
}

void
sanguis::server::global::context::player_change_shooting(
	sanguis::server::player_id const _player_id,
	bool const _shooting,
	sanguis::is_primary_weapon const _is_primary
)
{
	this->player(
		_player_id
	).use_weapon(
		_shooting,
		_is_primary
	);
}

void
sanguis::server::global::context::player_drop_or_pickup_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::is_primary_weapon const _is_primary
)
{
	this->player(
		_player_id
	).drop_or_pickup_weapon(
		_is_primary
	);
}

void
sanguis::server::global::context::player_speed(
	sanguis::server::player_id const _player_id,
	sanguis::server::speed const &_speed
)
{
	sanguis::server::entities::player &player_ref(
		this->player(
			_player_id
		)
	);

	player_ref.change_speed(
		_speed
	);

	this->send_to_player(
		_player_id,
		*sanguis::messages::create(
			sanguis::messages::speed(
				player_ref.id(),
				player_ref.speed().get()
			)
		)
	);
}

void
sanguis::server::global::context::player_position(
	sanguis::server::player_id const _player_id,
	sanguis::server::center const &_center
)
{
	this->player(
		_player_id
	).center_from_client(
		_center
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
		this->player(
			_player_id
		),
		_cheat
	);
}

void
sanguis::server::global::context::player_choose_perk(
	sanguis::server::player_id const _player_id,
	sanguis::perk_type const _perk_type
)
{
	sanguis::server::entities::player &player_ref(
		this->player(
			_player_id
		)
	);

	if(
		!player_ref.perk_choosable(
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

	player_ref.add_perk(
		sanguis::server::perks::create(
			diff_clock_,
			random_generator_,
			_perk_type
		)
	);

	sanguis::server::send_available_perks(
		player_ref,
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
		auto const &cur_world
		:
		worlds_.worlds()
	)
		cur_world.second->update();
}

bool
sanguis::server::global::context::multiple_players() const
{
	return
		players_.size()
		>
		1u;
}

bool
sanguis::server::global::context::has_player(
	sanguis::server::player_id const _player_id
) const
{
	return
		players_.count(
			_player_id
		)
		== 1u;
}

sanguis::entity_id const
sanguis::server::global::context::next_id()
{
	return
		next_id_++;
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

bool
sanguis::server::global::context::request_transfer(
	sanguis::server::global::source_world_pair const _source
) const
{
	return
		worlds_.connections().count(
			_source
		)
		!=
		0u;
}

void
sanguis::server::global::context::transfer_entity(
	sanguis::server::global::source_world_pair const _source,
	sanguis::server::entities::unique_ptr &&_entity
)
{
	sanguis::server::global::world_connection_map const &connections(
		worlds_.connections()
	);

	auto const it(
		connections.find(
			_source
		)
	);

	FCPPT_ASSERT_ERROR(
		it != connections.end()
	);

	this->world(
		it->second.first.get()
	).insert(
		std::move(
			_entity
		),
		sanguis::server::entities::insert_parameters(
			sanguis::server::world::grid_pos_to_center(
				it->second.second.get()
			),
			sanguis::server::angle(
				0.f // TODO!
			)
		)
	);
}

sanguis::server::world::object &
sanguis::server::global::context::world(
	sanguis::world_id const _world_id
)
{
	sanguis::server::world::map const &worlds(
		worlds_.worlds()
	);

	auto const it(
		worlds.find(
			_world_id
		)
	);

	FCPPT_ASSERT_PRE(
		it != worlds.end()
	);

	return
		*it->second;
}

sanguis::server::entities::player &
sanguis::server::global::context::player(
	sanguis::server::player_id const _player_id
)
{
	auto const it(
		players_.find(
			_player_id
		)
	);

	FCPPT_ASSERT_PRE(
		it != players_.end()
	);

	return
		*it->second;
}
