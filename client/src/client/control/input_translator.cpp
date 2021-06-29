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
#include <sge/input/event_base.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/key/code.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
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
	sanguis::client::control::actions::callback &&_callback
)
:
	callback_(
		std::move(
			_callback
		)
	)
{
}

sanguis::client::control::input_translator::~input_translator()
= default;

void
sanguis::client::control::input_translator::on_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			fcppt::mpl::list::object<
				sge::input::focus::event::key const,
				sge::input::cursor::event::move const,
				sge::input::cursor::event::button const
			>,
			fcppt::cast::dynamic_fun
		>(
			_event
		),
		[
			this
		](
			auto const &_variant
		)
		{
			fcppt::variant::match(
				_variant,
				[
					this
				](
					fcppt::reference<
						sge::input::focus::event::key const
					> const _key_event
				)
				{
					this->key_event(
						_key_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::move const
					> const _move_event
				)
				{
					this->move_event(
						_move_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::button const
					> const _button_event
				)
				{
					this->button_event(
						_button_event.get()
					);
				}
			);
		}
	);
}

void
sanguis::client::control::input_translator::key_event(
	sge::input::focus::event::key const &_event
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

	// FIXME: Don't hardcode key_codes
	switch(
		_event.get().code()
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

	FCPPT_PP_POP_WARNING
}

void
sanguis::client::control::input_translator::move_event(
	sge::input::cursor::event::move const &_event
)
{
	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::variant(
				sanguis::client::control::actions::cursor(
					fcppt::optional::map(
						_event.position(),
						[](
							sge::input::cursor::position const &_position
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
sanguis::client::control::input_translator::button_event(
	sge::input::cursor::event::button const &_event
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

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

	FCPPT_PP_POP_WARNING
}

void
sanguis::client::control::input_translator::direction_event(
	sge::input::focus::event::key const &_event
)
{
	callback_(
		sanguis::client::control::actions::any(
			sanguis::client::control::actions::variant(
				sanguis::client::control::actions::scale(
					::key_scale_type(
						_event.get().code()
					),
					::key_scale_value(
						_event.get().code(),
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
	{
		return;
	}

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
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

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

	FCPPT_PP_POP_WARNING

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

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

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

	FCPPT_PP_POP_WARNING

	FCPPT_ASSERT_UNREACHABLE;
}

}
