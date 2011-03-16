#include "object.hpp"

sanguis::client::gui::menu::callbacks::object::object(
	callbacks::connect const &_connect,
	callbacks::cancel_connect const &_cancel_connect,
	callbacks::start_server const &_start_server,
	callbacks::quit const &_quit
)
: 
	connect_(_connect),
	cancel_connect_(_cancel_connect),
	start_server_(_start_server),
	quit_(_quit)
{
}

sanguis::client::gui::menu::callbacks::connect const &
sanguis::client::gui::menu::callbacks::object::connect() const
{
	return connect_;
}

sanguis::client::gui::menu::callbacks::cancel_connect const &
sanguis::client::gui::menu::callbacks::object::cancel_connect() const
{
	return cancel_connect_;
}

sanguis::client::gui::menu::callbacks::start_server const &
sanguis::client::gui::menu::callbacks::object::start_server() const
{
	return start_server_;
}

sanguis::client::gui::menu::callbacks::quit const &
sanguis::client::gui::menu::callbacks::object::quit() const
{
	return quit_;
}
