#include "input_translator.hpp"
#include "player_action.hpp"
#include "axis_direction_max.hpp"
#include "axis_direction_min.hpp"
#include "../cursor/object.hpp"
#include "../../exception.hpp"
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

sanguis::client::control::input_translator::input_translator(
	sge::input::keyboard::device_ptr const _keyboard,
	client::cursor::object &_cursor,
	post_fun const &_post_message
)
:
	post_message_(_post_message),
	key_connection_(
		_keyboard->key_callback(
			std::tr1::bind(
				&input_translator::key_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	axis_connection_(
		_cursor.move_callback(
			std::tr1::bind(
				&input_translator::move_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	button_connection_(
		_cursor.button_callback(
			std::tr1::bind(
				&input_translator::button_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

sanguis::client::control::input_translator::~input_translator()
{
}

void
sanguis::client::control::input_translator::key_callback(
	sge::input::keyboard::key_event const &_event
)
{
	switch(
		_event.key_code()
	)
	{
	case sge::input::keyboard::key_code::a:
	case sge::input::keyboard::key_code::d:
	case sge::input::keyboard::key_code::w:
	case sge::input::keyboard::key_code::s:
		direction_event(
			_event
		);
		break;
	case sge::input::keyboard::key_code::x:
		weapon_switch_event(
			_event.pressed(),
			action_type::switch_weapon_forwards
		);
		break;
	case sge::input::keyboard::key_code::c:
		weapon_switch_event(
			_event.pressed(),
			action_type::switch_weapon_backwards
		);
		break;
	case sge::input::keyboard::key_code::e:
		perk_event(
			_event.pressed()
		);
		break;
	case sge::input::keyboard::key_code::escape:
		escape_event(
			_event.pressed()
		);
		break;
	default:
		break;
	}
}

void
sanguis::client::control::input_translator::move_callback(
	sge::input::cursor::move_event const &_event
)
{
#if 0
	switch(
		_event.axis()
	)
	{
	case sge::input::mouse::axis::x:
		rotation_event(
			_event.axis_value(),
			action_type::horizontal_look
		);
		break;
	case sge::input::mouse::axis::y:
		rotation_event(
			_event.axis_value(),
			action_type::vertical_look
		);
		break;
	default:
		break;
	}
#endif
}

void
sanguis::client::control::input_translator::button_callback(
	sge::input::cursor::button_event const &_event
)
{
	if(
		_event.button_code() == sge::input::cursor::button_code::left
	)
		post_message_(
			player_action(
				action_type::shoot,
				_event.pressed()
			)
		);
}

void
sanguis::client::control::input_translator::direction_event(
	sge::input::keyboard::key_event const &_event
)
{
	key_scale scale(
		_event.pressed()
		?
			control::axis_direction_max()
		:
			control::axis_direction_min()
	);

	action_type::type to_send;

	switch(
		_event.key_code()
	)
	{
	case sge::input::keyboard::key_code::a:
		scale = -scale;
	case sge::input::keyboard::key_code::d:
		to_send = action_type::horizontal_move;
		break;
	case sge::input::keyboard::key_code::w:
		scale = -scale;
	case sge::input::keyboard::key_code::s:
		to_send = action_type::vertical_move;
		break;
	default:
		throw sanguis::exception(
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
	sge::input::cursor::position_unit const _value,
	action_type::type const _action
)
{
	post_message_(
		player_action(
			_action,
			static_cast<
				key_scale
			>(
				_value
			)
		)
	);
}

void
sanguis::client::control::input_translator::weapon_switch_event(
	bool const _pressed,
	action_type::type const _action
)
{
	if(
		!_pressed
	)
		return;

	post_message_(
		player_action(
			_action,
			static_cast<
				key_scale
			>(
				0
			)
		)
	);
}

void
sanguis::client::control::input_translator::perk_event(
	bool const _pressed
)
{
	if(
		!_pressed
	)
		return;

	post_message_(
		player_action(
			action_type::perk_menu,
			static_cast<
				key_scale
			>(
				1 // FIXME!
			)
		)
	);
}

void
sanguis::client::control::input_translator::escape_event(
	bool const _pressed
)
{
	if(
		!_pressed
	)
		return;

	post_message_(
		player_action(
			action_type::escape,
			static_cast<
				key_scale
			>(
				1 // FIXME!
			)
		)
	);
}
