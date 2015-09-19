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
#include <sanguis/client/control/actions/variant.hpp>
#include <sge/input/cursor/activatable.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::control::actions::scale_type
key_scale_type(
	sge::input::key::code
);

sanguis::client::control::key_scale
key_scale_value(
	sge::input::key::code,
	bool pressed
);

}

sanguis::client::control::input_translator::input_translator(
	sge::input::focus::object &_focus,
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
		_focus.key_callback(
			sge::input::focus::key_callback{
				std::bind(
					&sanguis::client::control::input_translator::key_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	axis_connection_(
		cursor_.move_callback(
			sge::input::cursor::move_callback{
				std::bind(
					&sanguis::client::control::input_translator::move_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	button_connection_(
		cursor_.button_callback(
			sge::input::cursor::button_callback{
				std::bind(
					&sanguis::client::control::input_translator::button_callback,
					this,
					std::placeholders::_1
				)
			}
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
	sge::input::focus::key_event const &_event
)
{
	// FIXME: Don't hardcode key_codes
	switch(
		_event.key().code()
	)
	{
	case sge::input::key::code::a:
	case sge::input::key::code::d:
	case sge::input::key::code::w:
	case sge::input::key::code::s:
		this->direction_event(
			_event
		);
		break;
	case sge::input::key::code::x:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::drop_primary_weapon
		);
		break;
	case sge::input::key::code::c:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::drop_secondary_weapon
		);
		break;
	case sge::input::key::code::f1:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::console
		);
		break;
	case sge::input::key::code::e:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::perk_menu
		);
		break;
	case sge::input::key::code::escape:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::escape
		);
		break;
	case sge::input::key::code::r:
		this->nullary_event(
			_event.pressed(),
			sanguis::client::control::actions::nullary_type::reload_primary_weapon
		);
		break;
	case sge::input::key::code::space:
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
			sanguis::client::control::actions::variant(
				sanguis::client::control::actions::cursor(
					fcppt::optional_bind_construct(
						_event.position(),
						[](
							sge::input::cursor::position const _position
						)
						{
							return
								fcppt::math::vector::structure_cast<
									sanguis::client::control::cursor_position,
									fcppt::cast::size_fun
								>(
									_position
								);
						}
					)
				)
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
	sge::input::focus::key_event const &_event
)
{
	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::variant(
				sanguis::client::control::actions::scale(
					::key_scale_type(
						_event.key().code()
					),
					::key_scale_value(
						_event.key().code(),
						_event.pressed()
					)
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
			sanguis::client::control::actions::variant(
				sanguis::client::control::actions::nullary(
					_action
				)
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
			sanguis::client::control::actions::variant(
				sanguis::client::control::actions::binary(
					_action,
					_pressed
				)
			)
		)
	);
}

namespace
{

sanguis::client::control::actions::scale_type
key_scale_type(
	sge::input::key::code const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::key::code::a:
	case sge::input::key::code::d:
		return sanguis::client::control::actions::scale_type::horizontal_move;
	case sge::input::key::code::w:
	case sge::input::key::code::s:
		return sanguis::client::control::actions::scale_type::vertical_move;
	default:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::client::control::key_scale
key_scale_value(
	sge::input::key::code const _code,
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
	case sge::input::key::code::w:
	case sge::input::key::code::a:
		return -scale;
	case sge::input::key::code::s:
	case sge::input::key::code::d:
		return scale;
	default:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}
