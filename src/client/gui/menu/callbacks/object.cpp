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
