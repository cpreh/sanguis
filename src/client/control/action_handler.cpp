#include <sanguis/cheat_type.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/control/action_handler.hpp>
#include <sanguis/client/control/action_visitor.hpp>
#include <sanguis/client/control/axis_direction_max.hpp>
#include <sanguis/client/control/axis_direction_min.hpp>
#include <sanguis/client/control/direction_vector.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/optional_attack_dest.hpp>
#include <sanguis/client/control/scalar.hpp>
#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/binary.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/player_attack_dest.hpp>
#include <sanguis/messages/player_change_world.hpp>
#include <sanguis/messages/player_cheat.hpp>
#include <sanguis/messages/player_direction.hpp>
#include <sanguis/messages/player_drop_or_pickup_weapon.hpp>
#include <sanguis/messages/player_start_shooting.hpp>
#include <sanguis/messages/player_stop_shooting.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/callback/short_description.hpp>
#include <sge/font/lit.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::control::action_handler::action_handler(
	sanguis::client::send_callback const &_send,
	sanguis::client::control::environment &_environment,
	sge::console::object &_console
)
:
	send_(
		_send
	),
	environment_(
		_environment
	),
	rotation_timer_(
		sanguis::timer::parameters(
			std::chrono::milliseconds(
				100
			)
		)
	),
	direction_(
		sanguis::client::control::direction_vector::null()
	),
	cheat_connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			this->cheat_connection(
				_console,
				sanguis::cheat_type::exp,
				sge::console::callback::name(
					SGE_FONT_LIT("exp")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Get a lot of exp")
				)
			)
		)(
			this->cheat_connection(
				_console,
				sanguis::cheat_type::kill,
				sge::console::callback::name(
					SGE_FONT_LIT("kill")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Commit suicide")
				)
			)
		)(
			this->cheat_connection(
				_console,
				sanguis::cheat_type::monster_pickup,
				sge::console::callback::name(
					SGE_FONT_LIT("monster_pickup")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a monster pickup")
				)
			)
		)(
			this->cheat_connection(
				_console,
				sanguis::cheat_type::sentry_pickup,
				sge::console::callback::name(
					SGE_FONT_LIT("sentry_pickup")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a sentry pickup")
				)
			)
		)(
			this->cheat_connection(
				_console,
				sanguis::cheat_type::grenade_pickup,
				sge::console::callback::name(
					SGE_FONT_LIT("grenade_pickup")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Spawn a grenade pickup")
				)
			)
		)
		.move_container()
	)
{
}

sanguis::client::control::action_handler::~action_handler()
{
}

void
sanguis::client::control::action_handler::handle_action(
	sanguis::client::control::actions::any const &_action
)
{
	fcppt::variant::apply_unary(
		sanguis::client::control::action_visitor(
			*this
		),
		_action.get()
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
	if(
		!sge::timer::reset_when_expired(
			rotation_timer_
		)
	)
		return;

	environment_.update_position(
		_action.position()
	);

	if(
		!_action.position()
	)
		return;

	sanguis::client::control::optional_attack_dest const dest(
		environment_.translate_attack_dest(
			*_action.position()
		)
	);

	if(
		!dest
	)
		return;

	send_(
		*sanguis::messages::create(
			sanguis::messages::player_attack_dest(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
				>(
					*dest
				)
			)
		)
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
			*sanguis::messages::create(
				sanguis::messages::player_change_world()
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
			direction_.x(),
			scale
		);

		return;
	case sanguis::client::control::actions::scale_type::vertical_move:
		this->update_direction(
			direction_.y(),
			scale
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

void
sanguis::client::control::action_handler::update_direction(
	sanguis::client::control::scalar &_result,
	sanguis::client::control::key_scale const _scale
)
{
	_result =
		fcppt::math::clamp(
			_result + _scale,
			sanguis::client::control::axis_direction_min(),
			sanguis::client::control::axis_direction_max()
		);

	send_(
		*sanguis::messages::create(
			sanguis::messages::player_direction(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
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
		send_(
			*sanguis::messages::create(
				sanguis::messages::player_start_shooting(
					_is_primary
				)
			)
		);
	else
		send_(
			*sanguis::messages::create(
				sanguis::messages::player_stop_shooting(
					_is_primary
				)
			)
		);
}

void
sanguis::client::control::action_handler::handle_drop(
	sanguis::is_primary_weapon const _is_primary
)
{
	send_(
		*sanguis::messages::create(
			sanguis::messages::player_drop_or_pickup_weapon(
				_is_primary
			)
		)
	);
}

void
sanguis::client::control::action_handler::send_cheat(
	sanguis::cheat_type const _cheat,
	sge::console::arg_list const &,
	sge::console::object &
)
{
	send_(
		*sanguis::messages::create(
			sanguis::messages::player_cheat(
				_cheat
			)
		)
	);
}

fcppt::signal::auto_connection
sanguis::client::control::action_handler::cheat_connection(
	sge::console::object &_console,
	sanguis::cheat_type const _cheat,
	sge::console::callback::name const &_name,
	sge::console::callback::short_description const &_description
)
{
	return
		_console.insert(
			sge::console::callback::parameters(
				std::bind(
					&sanguis::client::control::action_handler::send_cheat,
					this,
					_cheat,
					std::placeholders::_1,
					std::placeholders::_2
				),
				_name
			)
			.short_description(
				_description.get()
			)
		);
}
