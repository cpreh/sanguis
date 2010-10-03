#include "input_translator.hpp"
#include "player_action.hpp"
#include "axis_direction_max.hpp"
#include "axis_direction_min.hpp"
#include "../../exception.hpp"
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

sanguis::client::control::input_translator::input_translator(
	sge::input::system_ptr const _input_sys,
	post_fun const &_post_message
)
:
	post_message_(_post_message),
	connection_(
		_input_sys->register_callback(
			std::tr1::bind(
				&input_translator::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	last_x_(0),
	last_y_(0)
{}

void
sanguis::client::control::input_translator::input_callback(
	sge::input::key_pair const &_key_pair
)
{
	sge::input::key_code const code(
		_key_pair.key().code()
	);

	switch(
		code
	)
	{
	case sge::input::kc::key_a:
	case sge::input::kc::key_d:
	case sge::input::kc::key_w:
	case sge::input::kc::key_s:
		direction_event(
			_key_pair
		);
		break;
	case sge::input::kc::mouse_x_axis:
	case sge::input::kc::mouse_y_axis:
		rotation_event(
			_key_pair
		);
		break;
	case sge::input::kc::mouse_l:
		shooting_event(
			_key_pair
		);
		break;
	case sge::input::kc::key_x:
	case sge::input::kc::key_c:
		weapon_switch_event(
			_key_pair
		);
		break;
	case sge::input::kc::key_e:
		perk_event(
			_key_pair
		);
		break;
	case sge::input::kc::key_escape:
		escape_event(
			_key_pair
		);
		break;
	default:
		break;
	}
}

void
sanguis::client::control::input_translator::direction_event(
	sge::input::key_pair const &_key_pair
)
{
	key_scale scale(
		_key_pair.value()
		?
			control::axis_direction_max()
		:
			control::axis_direction_min()
	);

	action_type::type to_send;

	switch(
		_key_pair.key().code()
	)
	{
	case sge::input::kc::key_a:
		scale = -scale;
	case sge::input::kc::key_d:
		to_send = action_type::horizontal_move;
		break;
	case sge::input::kc::key_w:
		scale = -scale;
	case sge::input::kc::key_s:
		to_send = action_type::vertical_move;
		break;
	default:
		throw exception(
			FCPPT_TEXT("direction_event: impossible!")
		);
	}

	post_message_(
		player_action(
			to_send,
			scale
		)
	);
}

void
sanguis::client::control::input_translator::rotation_event(
	sge::input::key_pair const &_key_pair
)
{
	action_type::type to_send;

	switch(
		_key_pair.key().code()
	)
	{
	case sge::input::kc::mouse_x_axis:
		to_send = action_type::horizontal_look;
		break;
	case sge::input::kc::mouse_y_axis:
		to_send = action_type::vertical_look;
		break;
	default:
		throw exception(
			FCPPT_TEXT("rotation_event: impossible!")
		);
	}

	post_message_(
		player_action(
			to_send,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}

void
sanguis::client::control::input_translator::shooting_event(
	sge::input::key_pair const &_key_pair
)
{
	post_message_(
		player_action(
			action_type::shoot,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}
	
void
sanguis::client::control::input_translator::weapon_switch_event(
	sge::input::key_pair const &_key_pair
)
{
	if(
		!_key_pair.value()
	)
		return;

	post_message_(
		player_action(
			_key_pair.key().code() == sge::input::kc::key_x
			?
				action_type::switch_weapon_backwards
			:
				action_type::switch_weapon_forwards,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}

void
sanguis::client::control::input_translator::perk_event(
	sge::input::key_pair const &_key_pair
)
{
	if(
		!_key_pair.value()
	)
		return;

	post_message_(
		player_action(
			action_type::perk_menu,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}

void
sanguis::client::control::input_translator::escape_event(
	sge::input::key_pair const &_key_pair
)
{
	if(
		!_key_pair.value()
	)
		return;

	post_message_(
		player_action(
			action_type::escape,
			static_cast<
				key_scale
			>(
				_key_pair.value()
			)
		)
	);
}
