#include <sanguis/cheat_type.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/control/action_handler.hpp>
#include <sanguis/client/control/action_visitor.hpp>
#include <sanguis/client/control/axis_direction_max.hpp>
#include <sanguis/client/control/axis_direction_min.hpp>
#include <sanguis/client/control/direction_vector.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/scalar.hpp>
#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/binary.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/player_attack_dest.hpp>
#include <sanguis/messages/player_direction.hpp>
#include <sanguis/messages/player_start_shooting.hpp>
#include <sanguis/messages/player_stop_shooting.hpp>
#include <sanguis/messages/player_change_weapon.hpp>
#include <sanguis/messages/player_cheat.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/lit.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/cyclic_iterator.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
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
	current_weapon_(
		sanguis::weapon_type::none
	),
	rotation_timer_(
		sanguis::timer::parameters(
			boost::chrono::milliseconds(
				100
			)
		)
	),
	owned_weapons_(),
	direction_(
		sanguis::client::control::direction_vector::null()
	),
	cheat_kill_conn_(
		_console.insert(
			sge::console::callback::parameters(
				std::bind(
					&sanguis::client::control::action_handler::send_cheat,
					this,
					sanguis::cheat_type::kill,
					std::placeholders::_1,
					std::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_LIT("kill")
				)
			)
			.short_description(
				SGE_FONT_LIT("Commit suicide")
			)
		)
	),
	cheat_impulse_conn_(
		_console.insert(
			sge::console::callback::parameters(
				std::bind(
					&sanguis::client::control::action_handler::send_cheat,
					this,
					sanguis::cheat_type::impulse101,
					std::placeholders::_1,
					std::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_LIT("impulse")
				)
			)
			.short_description(
				SGE_FONT_LIT("Get all weapons")
			)
		)
	),
	cheat_exp_conn_(
		_console.insert(
			sge::console::callback::parameters(
				std::bind(
					&sanguis::client::control::action_handler::send_cheat,
					this,
					sanguis::cheat_type::exp,
					std::placeholders::_1,
					std::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_LIT("exp")
				)
			)
			.short_description(
				SGE_FONT_LIT("Get a lot of exp")
			)
		)
	)
{
	std::fill(
		owned_weapons_.begin(),
		owned_weapons_.end(),
		false
	);
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
sanguis::client::control::action_handler::give_player_weapon(
	sanguis::weapon_type const _weapon_type
)
{
	owned_weapons_.at(
		static_cast<
			owned_weapons_array::size_type
		>(
			_weapon_type
		)
	) = true;

	// we don't own any weapon so take this one
	if(
		current_weapon_ == sanguis::weapon_type::none
	)
		this->change_weapon(
			_weapon_type
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
	case sanguis::client::control::actions::binary_type::shoot:
		this->handle_shooting(
			_action.value()
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

	send_(
		*sanguis::messages::create(
			sanguis::messages::player_attack_dest(
				fcppt::math::vector::structure_cast<
					sanguis::messages::types::vector2
				>(
					environment_.translate_attack_dest(
						_action.position()
					)
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
	case sanguis::client::control::actions::nullary_type::switch_weapon_forwards:
		this->handle_switch_weapon(
			true
		);

		return;
	case sanguis::client::control::actions::nullary_type::switch_weapon_backwards:
		this->handle_switch_weapon(
			false
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
	bool const _value
)
{
	if(
		_value
	)
		send_(
			*sanguis::messages::create(
				sanguis::messages::player_start_shooting()
			)
		);
	else
		send_(
			*sanguis::messages::create(
				sanguis::messages::player_stop_shooting()
			)
		);
}

void
sanguis::client::control::action_handler::handle_switch_weapon(
	bool const _forward
)
{
	// we don't own any weapon
	if(
		current_weapon_ == sanguis::weapon_type::none
	)
		return;

	owned_weapons_array::size_type const weapon_index(
		static_cast<
			owned_weapons_array::size_type
		>(
			current_weapon_
		)
	);

	FCPPT_ASSERT_ERROR(
		weapon_index < owned_weapons_.size()
	);

	typedef fcppt::cyclic_iterator<
		owned_weapons_array::const_iterator
	> iterator;

	iterator it(
		owned_weapons_.begin()
		+ static_cast<
			owned_weapons_array::size_type
		>(
			current_weapon_
		),
		owned_weapons_.begin(),
		owned_weapons_.end()
	);

	if(
		_forward
	)
		while(!*++it) ;
	else
		while(!*--it) ;

	this->change_weapon(
		static_cast<
			sanguis::weapon_type
		>(
			std::distance(
				static_cast<
					owned_weapons_array const &
				>(
					owned_weapons_
				).begin(),
				it.get()
			)
		)
	);
}

void
sanguis::client::control::action_handler::change_weapon(
	sanguis::weapon_type const _weapon_type
)
{
	current_weapon_ = _weapon_type;

	send_(
		*sanguis::messages::create(
			sanguis::messages::player_change_weapon(
				static_cast<
					sanguis::messages::types::enum_
				>(
					current_weapon_
				)
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
				static_cast<
					sanguis::messages::types::enum_
				>(
					_cheat
				)
			)
		)
	);
}
