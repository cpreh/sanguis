#include <sanguis/client/gui/menu/callbacks/object.hpp>

sanguis::client::gui::menu::callbacks::object::object(
	callbacks::connect const &_connect,
	callbacks::cancel_connect const &_cancel_connect,
	callbacks::quickstart const &_quickstart,
	callbacks::quit const &_quit
)
:
	connect_(_connect),
	cancel_connect_(_cancel_connect),
	quickstart_(_quickstart),
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

sanguis::client::gui::menu::callbacks::quickstart const &
sanguis::client::gui::menu::callbacks::object::quickstart() const
{
	return quickstart_;
}

sanguis::client::gui::menu::callbacks::quit const &
sanguis::client::gui::menu::callbacks::object::quit() const
{
	return quit_;
}
