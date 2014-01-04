#include <sanguis/client/control/axis_direction_max.hpp>
#include <sanguis/client/control/axis_direction_min.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/input_translator.hpp>
#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/binary.hpp>
#include <sanguis/client/control/actions/binary_type.hpp>
#include <sanguis/client/control/actions/callback.hpp>
#include <sanguis/client/control/actions/cursor.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/control/actions/scale.hpp>
#include <sanguis/client/control/actions/scale_type.hpp>
#include <sge/input/cursor/activatable.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::control::actions::scale_type
key_scale_type(
	sge::input::keyboard::key_code
);

sanguis::client::control::key_scale
key_scale_value(
	sge::input::keyboard::key_code,
	bool pressed
);

}

sanguis::client::control::input_translator::input_translator(
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor,
	sanguis::client::control::actions::callback const &_callback
)
:
	cursor_(
		_cursor
	),
	callback_(
		_callback
	),
	key_connection_(
		_keyboard.key_callback(
			std::bind(
				&sanguis::client::control::input_translator::key_callback,
				this,
				std::placeholders::_1
			)
		)
	),
	axis_connection_(
		cursor_.move_callback(
			std::bind(
				&sanguis::client::control::input_translator::move_callback,
				this,
				std::placeholders::_1
			)
		)
	),
	button_connection_(
		cursor_.button_callback(
			std::bind(
				&sanguis::client::control::input_translator::button_callback,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::client::control::input_translator::~input_translator()
{
}

sge::input::cursor::activatable &
sanguis::client::control::input_translator::cursor()
{
	return
		cursor_;
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
	case sge::input::keyboard::key_code::x:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::drop_primary_weapon
		);
		break;
	case sge::input::keyboard::key_code::c:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::drop_secondary_weapon
		);
		break;
	case sge::input::keyboard::key_code::f1:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::console
		);
		break;
	case sge::input::keyboard::key_code::e:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::perk_menu
		);
		break;
	case sge::input::keyboard::key_code::escape:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::escape
		);
		break;
	case sge::input::keyboard::key_code::r:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::reload_primary_weapon
		);
		break;
	case sge::input::keyboard::key_code::space:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::change_world
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
	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::cursor(
				_event.position()
				?
					sanguis::client::control::optional_cursor_position(
						fcppt::math::vector::structure_cast<
							sanguis::client::control::cursor_position
						>(
							*_event.position()
						)
					)
				:
					sanguis::client::control::optional_cursor_position()
			)
		)
	);
}

void
sanguis::client::control::input_translator::button_callback(
	sge::input::cursor::button_event const &_event
)
{
	switch(
		_event.button_code()
	)
	{
	case sge::input::cursor::button_code::left:
		this->binary_event(
			_event.pressed(),
			sanguis::client::control::actions::binary_type::shoot_primary
		);
		break;
	case sge::input::cursor::button_code::right:
		this->binary_event(
			_event.pressed(),
			sanguis::client::control::actions::binary_type::shoot_secondary
		);
		break;
	default:
		break;
	}
}

void
sanguis::client::control::input_translator::direction_event(
	sge::input::keyboard::key_event const &_event
)
{
	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::scale(
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
	sanguis::client::control::actions::nullary_type const _action
)
{
	if(
		!_pressed
	)
		return;

	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::nullary(
				_action
			)
		)
	);
}

void
sanguis::client::control::input_translator::binary_event(
	bool const _pressed,
	sanguis::client::control::actions::binary_type const _action
)
{
	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::binary(
				_action,
				_pressed
			)
		)
	);
}

namespace
{

sanguis::client::control::actions::scale_type
key_scale_type(
	sge::input::keyboard::key_code const _code
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

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::client::control::key_scale
key_scale_value(
	sge::input::keyboard::key_code const _code,
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

	FCPPT_ASSERT_UNREACHABLE;
}

}
