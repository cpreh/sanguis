#include <sanguis/client/cursor/object.hpp>
#include <sge/input/cursor/object.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::cursor::object::object(
	sge::input::cursor::object &_cursor
)
:
	cursor_(_cursor),
	button_signal_(),
	move_signal_(),
	button_connection_(
		cursor_.button_callback(
			std::tr1::bind(
				&object::on_button,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	move_connection_(
		cursor_.move_callback(
			std::tr1::bind(
				&object::on_move,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	active_(
		false
	)
{
}

sanguis::client::cursor::object::~object()
{
}

fcppt::signal::auto_connection
sanguis::client::cursor::object::button_callback(
	sge::input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::client::cursor::object::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

void
sanguis::client::cursor::object::active(
	bool const _active
)
{
	active_ = _active;
}

bool
sanguis::client::cursor::object::active() const
{
	return active_;
}

sge::input::cursor::position const
sanguis::client::cursor::object::position() const
{
	return cursor_.position();
}

sge::input::cursor::object &
sanguis::client::cursor::object::get() const
{
	return cursor_;
}

void
sanguis::client::cursor::object::on_button(
	sge::input::cursor::button_event const &_event
)
{
	if(
		active_
	)
		button_signal_(
			_event
		);
}

void
sanguis::client::cursor::object::on_move(
	sge::input::cursor::move_event const &_event
)
{
	if(
		active_
	)
		move_signal_(
			_event
		);
}
