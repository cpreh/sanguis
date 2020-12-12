#include <sanguis/cheat_type.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/random_seed.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/connected.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/remove_id.hpp>
#include <sanguis/messages/server/rotate.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/create_player.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/load_fwd.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/unknown_player_exception.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/cheat/process.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/insert_with_result.hpp>
#include <sanguis/server/entities/optional_player_ref.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/global/dest_world_pair.hpp>
#include <sanguis/server/global/generate_worlds.hpp>
#include <sanguis/server/global/load_context.hpp>
#include <sanguis/server/global/next_id_callback.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/world/context.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/map.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <alda/message/init_record.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/signed_angle_between.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::global::context::context(
	fcppt::log::context_reference const _log_context,
	sanguis::server::unicast_callback const &_send_unicast,
	sanguis::server::load const &_model_context,
	sanguis::server::console &_console
)
:
	sanguis::server::world::context(),
	log_{
		_log_context,
		sanguis::server::log_location()
		/
		fcppt::log::name{
			FCPPT_TEXT("global")
		},
		fcppt::log::parameters_no_function(
			fcppt::log::name{
				FCPPT_TEXT("context")
			}
		)
	},
	weapons_log_{
		_log_context,
	},
	random_generator_(
		sanguis::random_seed()
	),
	next_id_(
		0u
	),
	send_unicast_(
		_send_unicast
	),
	load_context_(
		fcppt::unique_ptr_to_base<
			sanguis::server::environment::load_context
		>(
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
		)
	),
	console_(
		_console
	),
	players_(),
	worlds_(
		sanguis::server::global::generate_worlds(
			sanguis::server::world::parameters(
				_log_context,
				random_generator_,
				this->weapon_parameters(),
				*this,
				*load_context_
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::server::global::context::~context()
{
}

void
sanguis::server::global::context::insert_player(
	sanguis::world_id const _world_id,
	sanguis::server::player_id const _player_id,
	sanguis::player_name const &_name
)
{
	// send this before the world gets created
	this->send_to_player(
		_player_id,
		sanguis::messages::server::create(
			sanguis::messages::server::connected(
				fcppt::unit{}
			)
		)
	);

	sanguis::server::entities::player_unique_ptr player_ptr(
		sanguis::server::create_player(
			random_generator_,
			this->weapon_parameters(),
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
			fcppt::make_ref(
				*player_ptr
			)
		)
	);

	fcppt::optional::maybe(
		fcppt::optional::bind(
			fcppt::optional::copy_value(
				fcppt::container::at_optional(
					cur_world.openings()[
						sanguis::creator::opening_type::entry
					],
					0u
				)
			),
			[
				&cur_world,
				&player_ptr
			](
				sanguis::creator::opening const _opening
			)
			{
				return
					sanguis::server::entities::insert_with_result<
						sanguis::server::entities::with_id
					>(
						cur_world,
						std::move(
							player_ptr
						),
						sanguis::server::entities::insert_parameters(
							sanguis::server::world::grid_pos_to_center(
								_opening.get()
							),
							sanguis::server::angle(
								0.f
							)
						)
					);
			}
		),
		[
			this
		]{
			FCPPT_LOG_ERROR(
				log_,
				fcppt::log::out
					<< FCPPT_TEXT("Unable to insert a player!")
			)
		},
		[
			&cur_world,
			this
		](
			fcppt::reference<
				sanguis::server::entities::player
			> const _player
		)
		{
			fcppt::optional::maybe_void(
				_player.get().primary_weapon(),
				[
					&cur_world,
					_player
				](
					fcppt::reference<
						sanguis::server::weapons::weapon const
					> const _weapon
				)
				{
					cur_world.got_weapon(
						_player.get().player_id(),
						_weapon.get().description()
					);
				}
			);

			cur_world.level_changed(
				_player.get().player_id(),
				_player.get().level()
			);

			sanguis::server::send_available_perks(
				_player.get(),
				send_unicast_
			);
		}
	);
}

void
sanguis::server::global::context::player_disconnect(
	sanguis::server::player_id const _player_id
)
{
	// Disconnecting clients may already be dead
	fcppt::optional::maybe(
		this->player_opt(
			_player_id
		),
		[
			this,
			_player_id
		]{
			FCPPT_LOG_INFO(
				log_,
				fcppt::log::out
					<< FCPPT_TEXT("Player ")
					<< _player_id
					<< FCPPT_TEXT(" is already dead.")
			)
		},
		[](
			fcppt::reference<
				sanguis::server::entities::player
			> const _player
		)
		{
			_player.get().kill();
		}
	);
}

void
sanguis::server::global::context::player_target(
	sanguis::server::player_id const _player_id,
	sanguis::server::vector const &_target
)
{
	// handles rotation as well
	sanguis::server::entities::player &player(
		this->player_exn(
			_player_id
		)
	);

	player.target(
		sanguis::server::weapons::optional_target(
			sanguis::server::weapons::target(
				_target
			)
		)
	);

	sanguis::server::vector const player_center(
		player.center().get()
	);

	fcppt::optional::maybe_void(
		fcppt::math::vector::signed_angle_between(
			player_center,
			_target
		),
		[
			&player
		](
			sanguis::server::space_unit const _angle
		)
		{
			player.angle(
				sanguis::server::angle(
					_angle
				)
			);
		}
	);

	this->send_to_player(
		_player_id,
		sanguis::messages::server::create(
			alda::message::init_record<
				sanguis::messages::server::rotate
			>(
				sanguis::messages::roles::entity_id{} =
					player.id(),
				sanguis::messages::roles::angle{} =
					player.angle().get()
			)
		)
	);
}

void
sanguis::server::global::context::player_change_world(
	sanguis::server::player_id const _player_id
)
{
	this->player_exn(
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
	this->player_exn(
		_player_id
	).use_weapon(
		_shooting,
		_is_primary
	);
}

void
sanguis::server::global::context::player_reload(
	sanguis::server::player_id const _player_id,
	sanguis::is_primary_weapon const _is_primary
)
{
	this->player_exn(
		_player_id
	).reload(
		_is_primary
	);
}

void
sanguis::server::global::context::player_drop_or_pickup_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::is_primary_weapon const _is_primary
)
{
	this->player_exn(
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
	sanguis::server::entities::player &player(
		this->player_exn(
			_player_id
		)
	);

	player.change_speed(
		_speed
	);

	this->send_to_player(
		_player_id,
		sanguis::messages::server::create(
			alda::message::init_record<
				sanguis::messages::server::speed
			>(
				sanguis::messages::roles::entity_id{} =
					player.id(),
				sanguis::messages::roles::speed{} =
					player.speed().get()
			)
		)
	);
}

void
sanguis::server::global::context::player_cheat(
	sanguis::server::player_id const _player_id,
	sanguis::cheat_type const _cheat
)
{
	sanguis::server::cheat::process(
		this->player_exn(
			_player_id
		),
		_cheat,
		this->weapon_parameters(),
		send_unicast_
	);
}

void
sanguis::server::global::context::player_choose_perk(
	sanguis::server::player_id const _player_id,
	sanguis::perk_type const _perk_type
)
{
	sanguis::server::entities::player &player(
		this->player_exn(
			_player_id
		)
	);

	if(
		!player.perk_choosable(
			_perk_type
		)
	)
	{
		FCPPT_LOG_WARNING(
			log_,
			fcppt::log::out
				<< FCPPT_TEXT("Player with id ")
				<< _player_id
				<< FCPPT_TEXT(" tried to take an invalid perk")
				<< FCPPT_TEXT(" or has no skillpoints left!")
		)

		return;
	}

	player.add_perk(
		_perk_type
	);
}

void
sanguis::server::global::context::update(
	sanguis::duration const &_diff
)
{
	for(
		auto const &cur_world
		:
		worlds_.worlds()
	)
		cur_world.second->update(
			_diff
		);
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
		==
		1u;
}

sanguis::entity_id
sanguis::server::global::context::next_id()
{
	return
		next_id_++;
}

void
sanguis::server::global::context::send_to_player(
	sanguis::server::player_id const _player_id,
	sanguis::messages::server::base const &_msg
)
{
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
		sanguis::messages::server::create(
			sanguis::messages::server::remove_id(
				fcppt::unit{}
			)
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
	sanguis::server::entities::with_id_unique_ptr &&_entity
)
{
	sanguis::server::global::dest_world_pair const dest(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_mapped(
				worlds_.connections(),
				_source
			)
		).get()
	);

	this->world(
		dest.first.get()
	).insert(
		std::move(
			_entity
		),
		sanguis::server::entities::insert_parameters(
			sanguis::server::world::grid_pos_to_center(
				dest.second.get()
			),
			sanguis::server::angle(
				0.f // TODO!
			),
			sanguis::collision::world::created{
				false
			}
		)
	);
}

sanguis::server::weapons::common_parameters
sanguis::server::global::context::weapon_parameters()
{
	return
		sanguis::server::weapons::common_parameters{
			weapons_log_,
			random_generator_
		};
}

sanguis::server::world::object &
sanguis::server::global::context::world(
	sanguis::world_id const _world_id
)
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_mapped(
				worlds_.worlds(),
				_world_id
			)
		).get();
}

sanguis::server::entities::player &
sanguis::server::global::context::player_exn(
	sanguis::server::player_id const _player_id
)
{
	return
		fcppt::optional::to_exception(
			this->player_opt(
				_player_id
			),
			[]{
				return
					sanguis::server::unknown_player_exception{};
			}
		).get();
}

sanguis::server::entities::optional_player_ref
sanguis::server::global::context::player_opt(
	sanguis::server::player_id const _player_id
)
{
	return
		fcppt::optional::map(
			fcppt::container::find_opt_mapped(
				players_,
				_player_id
			),
			[](
				fcppt::reference<
					player_ref
				> const _ref
			)
			{
				return
					_ref.get();
			}
		);
}
