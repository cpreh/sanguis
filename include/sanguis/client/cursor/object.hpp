#ifndef SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_OBJECT_HPP_INCLUDED

#include <sanguis/client/cursor/object_fwd.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace cursor
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit object(
		sge::input::cursor::object &
	);

	~object();

	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	);

	void
	active(
		bool
	);

	bool
	active() const;

	sge::input::cursor::object &
	get() const;
private:
	void
	on_button(
		sge::input::cursor::button_event const &
	);

	void
	on_move(
		sge::input::cursor::move_event const &
	);

	sge::input::cursor::object &cursor_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	fcppt::signal::scoped_connection const
		button_connection_,
		move_connection_;

	bool active_;
};

}
}
}

#endif // SANGUIS_CLIENT_CURSOR_HPP_INCLUDED
