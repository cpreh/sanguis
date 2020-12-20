#include <sanguis/cheat_type.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/control/action_handler.hpp>
#include <sanguis/client/control/attack_dest.hpp>
#include <sanguis/client/control/axis_direction_max.hpp>
#include <sanguis/client/control/axis_direction_min.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/direction_vector.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/environment_cref.hpp>
#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/scalar.hpp>
#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/binary.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <sanguis/messages/client/attack_dest.hpp>
#include <sanguis/messages/client/change_world.hpp>
#include <sanguis/messages/client/cheat.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/client/direction.hpp>
#include <sanguis/messages/client/drop_or_pickup_weapon.hpp>
#include <sanguis/messages/client/reload.hpp>
#include <sanguis/messages/client/start_shooting.hpp>
#include <sanguis/messages/client/stop_shooting.hpp>
#include <sanguis/messages/roles/attack_dest.hpp>
#include <sanguis/messages/roles/direction.hpp>
#include <alda/message/init_record.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/callback/short_description.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::control::action_handler::action_handler(
	sanguis::client::send_callback &&_send,
	sanguis::client::control::environment_cref const _environment,
	sge::console::object_ref const _console
)
:
	send_(
		std::move(
			_send
		)
	),
	environment_(
		_environment
	),
	rotation_timer_(
		sanguis::timer::parameters(
			std::chrono::milliseconds(
				100 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		)
	),
	direction_(
		fcppt::math::vector::null<
			sanguis::client::control::direction_vector
		>()
	),
	cursor_position_(),
	cheat_connections_(
		fcppt::container::make<
			fcppt::signal::auto_connection_container
		>(
			this->cheat_connection(
				_console,
				sanguis::cheat_type::auras,
				sge::console::callback::name(
					SGE_FONT_LIT("auras")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Get various auras")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::exp,
				sge::console::callback::name(
					SGE_FONT_LIT("exp")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Get a lot of exp")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::heal,
				sge::console::callback::name(
					SGE_FONT_LIT("heal")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Completely heal the player")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::kill,
				sge::console::callback::name(
					SGE_FONT_LIT("kill")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Commit suicide")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::spider,
				sge::console::callback::name(
					SGE_FONT_LIT("spider")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a spider weapon")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::monster_spawner,
				sge::console::callback::name(
					SGE_FONT_LIT("monster_spawner")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a monster creating weapon")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::perks,
				sge::console::callback::name(
					SGE_FONT_LIT("perks")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Get all perks")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::sentry,
				sge::console::callback::name(
					SGE_FONT_LIT("sentry")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a sentry")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::grenade,
				sge::console::callback::name(
					SGE_FONT_LIT("grenade")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a grenade")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::shotgun,
				sge::console::callback::name(
					SGE_FONT_LIT("shotgun")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a shotgun")
				)
			),
			this->cheat_connection(
				_console,
				sanguis::cheat_type::rocket_launcher,
				sge::console::callback::name(
					SGE_FONT_LIT("rocket_launcher")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a rocket launcher")
				)
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::client::control::action_handler::~action_handler()
= default;

void
sanguis::client::control::action_handler::handle_action(
	sanguis::client::control::actions::any const &_action_variant
)
{
	fcppt::variant::match(
		_action_variant.get(),
		[
			this
		](
			sanguis::client::control::actions::binary const &_action
		)
		{
			this->handle_binary_action(
				_action
			);
		},
		[
			this
		](
			sanguis::client::control::actions::cursor const &_action
		)
		{
			this->handle_cursor_action(
				_action
			);
		},
		[
			this
		](
			sanguis::client::control::actions::nullary const &_action
		)
		{
			this->handle_nullary_action(
				_action
			);
		},
		[
			this
		](
			sanguis::client::control::actions::scale const &_action
		)
		{
			this->handle_scale_action(
				_action
			);
		}
	);
}

void
sanguis::client::control::action_handler::handle_binary_action(
	sanguis::client::control::actions::binary const &_action
)
{
	switch(
		_action.type()
	)
	{
	case sanguis::client::control::actions::binary_type::shoot_primary:
		this->handle_shooting(
			_action.value(),
			sanguis::is_primary_weapon(
				true
			)
		);
		return;
	case sanguis::client::control::actions::binary_type::shoot_secondary:
		this->handle_shooting(
			_action.value(),
			sanguis::is_primary_weapon(
				false
			)
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

void
sanguis::client::control::action_handler::handle_cursor_action(
	sanguis::client::control::actions::cursor const &_action
)
{
	cursor_position_ =
		_action.position();

	if(
		!sge::timer::reset_when_expired(
			fcppt::make_ref(
				rotation_timer_
			)
		)
	)
	{
		return;
	}

	fcppt::optional::maybe_void(
		cursor_position_,
		[
			this
		](
			sanguis::client::control::cursor_position const &_pos
		)
		{
			fcppt::optional::maybe_void(
				environment_->translate_attack_dest(
					_pos
				),
				[
					this
				](
					sanguis::client::control::attack_dest const &_dest
				)
				{
					send_(
						sanguis::messages::client::create(
							alda::message::init_record<
								sanguis::messages::client::attack_dest
							>(
								sanguis::messages::roles::attack_dest{} =
									fcppt::math::vector::structure_cast<
										sanguis::messages::types::vector2,
										fcppt::cast::size_fun
									>(
										_dest
									)
								)
						)
					);
				}
			);
		}
	);
}

void
sanguis::client::control::action_handler::handle_nullary_action(
	sanguis::client::control::actions::nullary const &_action
)
{
	switch(
		_action.type()
	)
	{
	case sanguis::client::control::actions::nullary_type::change_world:
		send_(
			sanguis::messages::client::create(
				sanguis::messages::client::change_world(
					fcppt::unit{}
				)
			)
		);
		return;
	case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
		this->handle_drop(
			sanguis::is_primary_weapon(
				true
			)
		);
		return;
	case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
		this->handle_drop(
			sanguis::is_primary_weapon(
				false
			)
		);
		return;
	case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
		this->handle_reload(
			sanguis::is_primary_weapon(
				true
			)
		);
		return;
	case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
		this->handle_reload(
			sanguis::is_primary_weapon(
				false
			)
		);
		return;
	// There are some actions we don't handle
	case sanguis::client::control::actions::nullary_type::perk_menu:
	case sanguis::client::control::actions::nullary_type::escape:
	case sanguis::client::control::actions::nullary_type::console:
		break;
	}
}

void
sanguis::client::control::action_handler::handle_scale_action(
	sanguis::client::control::actions::scale const &_action
)
{
	sanguis::client::control::key_scale const scale(
		_action.get()
	);

	switch(
		_action.type()
	)
	{
	case sanguis::client::control::actions::scale_type::horizontal_move:
		this->update_direction(
			fcppt::make_ref(
				direction_.x()
			),
			scale
		);

		return;
	case sanguis::client::control::actions::scale_type::vertical_move:
		this->update_direction(
			fcppt::make_ref(
				direction_.y()
			),
			scale
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::client::control::optional_cursor_position const &
sanguis::client::control::action_handler::cursor_position() const
{
	return
		cursor_position_;
}

void
sanguis::client::control::action_handler::update_direction(
	fcppt::reference<
		sanguis::client::control::scalar
	> const _result,
	sanguis::client::control::key_scale const _scale
)
{
	_result.get() =
		fcppt::math::clamp(
			_result.get() + _scale,
			sanguis::client::control::axis_direction_min(),
			sanguis::client::control::axis_direction_max()
		);

	send_(
		sanguis::messages::client::create(
			alda::message::init_record<
				sanguis::messages::client::direction
			>(
				sanguis::messages::roles::direction{} =
					fcppt::math::vector::structure_cast<
						sanguis::messages::types::vector2,
						fcppt::cast::size_fun
					>(
						direction_
					)
				)
		)
	);
}

void
sanguis::client::control::action_handler::handle_shooting(
	bool const _value,
	sanguis::is_primary_weapon const _is_primary
)
{
	if(
		_value
	)
	{
		send_(
			sanguis::messages::client::create(
				sanguis::messages::client::start_shooting{
					_is_primary
				}
			)
		);
	}
	else
	{
		send_(
			sanguis::messages::client::create(
				sanguis::messages::client::stop_shooting{
					_is_primary
				}
			)
		);
	}
}

void
sanguis::client::control::action_handler::handle_drop(
	sanguis::is_primary_weapon const _is_primary
)
{
	send_(
		sanguis::messages::client::create(
			sanguis::messages::client::drop_or_pickup_weapon{
				_is_primary
			}
		)
	);
}

void
sanguis::client::control::action_handler::handle_reload(
	sanguis::is_primary_weapon const _is_primary
)
{
	send_(
		sanguis::messages::client::create(
			sanguis::messages::client::reload{
				_is_primary
			}
		)
	);
}

void
sanguis::client::control::action_handler::send_cheat(
	sanguis::cheat_type const _cheat,
	sge::console::arg_list const &
)
{
	send_(
		sanguis::messages::client::create(
			sanguis::messages::client::cheat{
				_cheat
			}
		)
	);
}

fcppt::signal::auto_connection
sanguis::client::control::action_handler::cheat_connection(
	sge::console::object_ref const _console,
	sanguis::cheat_type const _cheat,
	sge::console::callback::name const &_name,
	sge::console::callback::short_description const &_description
)
{
	return
		_console->insert(
			sge::console::callback::parameters(
				sge::console::callback::function{
					[
						_cheat,
						this
					](
						sge::console::arg_list const &_args,
						sge::console::object_ref
					)
					{
						this->send_cheat(
							_cheat,
							_args
						);
					}
				},
				fcppt::copy(
					_name
				)
			)
			.short_description(
				fcppt::copy(
					_description.get()
				)
			)
		);
}
