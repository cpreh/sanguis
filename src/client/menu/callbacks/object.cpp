#include "object.hpp"

sanguis::client::menu::callbacks::object::object(
	connect const &_connect,
	cancel_connect const &_cancel_connect,
	start_server const &_start_server,
	quit const &_quit)
: 
	connect_(_connect),
	cancel_connect_(_cancel_connect),
	start_server_(_start_server),
	quit_(_quit)
{
}
