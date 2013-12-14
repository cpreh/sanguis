#include <sanguis/client/cursor/object.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::cursor::object::object(
	sge::input::cursor::object &_cursor
)
:
	sge::input::cursor::object(),
	cursor_(
		_cursor
	),
	button_signal_(),
	move_signal_(),
	scroll_signal_(),
	button_connection_(
		cursor_.button_callback(
			std::bind(
				&sanguis::client::cursor::object::on_button,
				this,
				std::placeholders::_1
			)
		)
	),
	move_connection_(
		cursor_.move_callback(
			std::bind(
				&sanguis::client::cursor::object::on_move,
				this,
				std::placeholders::_1
			)
		)
	),
	scroll_connection_(
		cursor_.scroll_callback(
			std::bind(
				&sanguis::client::cursor::object::on_scroll,
				this,
				std::placeholders::_1
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

fcppt::signal::auto_connection
sanguis::client::cursor::object::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		scroll_signal_.connect(
			_callback
		);
}

sge::input::cursor::optional_position const
sanguis::client::cursor::object::position() const
{
	return
		active_
		?
			cursor_.position()
		:
			sge::input::cursor::optional_position()
		;
}

void
sanguis::client::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
	cursor_.mode(
		_mode
	);
}

void
sanguis::client::cursor::object::active(
	bool const _active
)
{
	active_ =
		_active;
}

bool
sanguis::client::cursor::object::active() const
{
	return
		active_;
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

void
sanguis::client::cursor::object::on_scroll(
	sge::input::cursor::scroll_event const &_event
)
{
	if(
		active_
	)
		scroll_signal_(
			_event
		);
}
