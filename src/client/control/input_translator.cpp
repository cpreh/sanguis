#include <sanguis/client/control/input_translator.hpp>
#include <sanguis/client/control/axis_direction_max.hpp>
#include <sanguis/client/control/axis_direction_min.hpp>
#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/binary.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <sanguis/client/control/actions/scale_type.hpp>
#include <sanguis/client/cursor/object.hpp>
#include <sanguis/exception.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

namespace
{

sanguis::client::control::actions::scale_type::type
key_scale_type(
	sge::input::keyboard::key_code::type
);

sanguis::client::control::key_scale
key_scale_value(
	sge::input::keyboard::key_code::type,
	bool pressed
);

}

sanguis::client::control::input_translator::input_translator(
	sge::input::keyboard::device &_keyboard,
	client::cursor::object &_cursor,
	actions::callback const &_callback
)
:
	callback_(_callback),
	key_connection_(
		_keyboard.key_callback(
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
		this->direction_event(
			_event
		);
		break;
	case sge::input::keyboard::key_code::f1:
		this->nullary_event(
			_event.pressed(),
			actions::nullary_type::console
		);
		break;
	case sge::input::keyboard::key_code::c:
		this->nullary_event(
			_event.pressed(),
			actions::nullary_type::switch_weapon_forwards
		);
		break;
	case sge::input::keyboard::key_code::x:
		this->nullary_event(
			_event.pressed(),
			actions::nullary_type::switch_weapon_backwards
		);
		break;
	case sge::input::keyboard::key_code::e:
		this->nullary_event(
			_event.pressed(),
			actions::nullary_type::perk_menu
		);
		break;
	case sge::input::keyboard::key_code::escape:
		this->nullary_event(
			_event.pressed(),
			actions::nullary_type::escape
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
	if(
		!_event.position()
	)
		return;

	callback_(
		actions::any(
			actions::cursor(
				*_event.position()
			)
		)
	);
}

void
sanguis::client::control::input_translator::button_callback(
	sge::input::cursor::button_event const &_event
)
{
	if(
		_event.button_code() == sge::input::cursor::button_code::left
	)
		callback_(
			actions::any(
				actions::binary(
					actions::binary_type::shoot,
					_event.pressed()
				)
			)
		);
}

void
sanguis::client::control::input_translator::direction_event(
	sge::input::keyboard::key_event const &_event
)
{
	callback_(
		actions::any(
			actions::scale(
				::key_scale_type(
					_event.key_code()
				),
				::key_scale_value(
					_event.key_code(),
					_event.pressed()
				)
			)
		)
	);
}

void
sanguis::client::control::input_translator::nullary_event(
	bool const _pressed,
	actions::nullary_type::type const _action
)
{
	if(
		!_pressed
	)
		return;

	callback_(
		actions::any(
			actions::nullary(
				_action
			)
		)
	);
}

namespace
{

sanguis::client::control::actions::scale_type::type
key_scale_type(
	sge::input::keyboard::key_code::type const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::keyboard::key_code::a:
	case sge::input::keyboard::key_code::d:
		return sanguis::client::control::actions::scale_type::horizontal_move;
	case sge::input::keyboard::key_code::w:
	case sge::input::keyboard::key_code::s:
		return sanguis::client::control::actions::scale_type::vertical_move;
	default:
		break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid key_code in key_scale_type()!")
	);
}

sanguis::client::control::key_scale
key_scale_value(
	sge::input::keyboard::key_code::type const _code,
	bool const _pressed
)
{
	sanguis::client::control::key_scale const scale(
		_pressed
		?
			sanguis::client::control::axis_direction_max()
		:
			sanguis::client::control::axis_direction_min()
	);

	switch(
		_code
	)
	{
	case sge::input::keyboard::key_code::w:
	case sge::input::keyboard::key_code::a:
		return -scale;
	case sge::input::keyboard::key_code::s:
	case sge::input::keyboard::key_code::d:
		return scale;
	default:
		break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid key_code in key_scale_value()!")
	);
}

}
