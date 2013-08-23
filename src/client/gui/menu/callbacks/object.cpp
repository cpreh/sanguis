#include <sanguis/client/gui/menu/callbacks/cancel_connect.hpp>
#include <sanguis/client/gui/menu/callbacks/connect.hpp>
#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <sanguis/client/gui/menu/callbacks/quickstart.hpp>
#include <sanguis/client/gui/menu/callbacks/quit.hpp>


sanguis::client::gui::menu::callbacks::object::object(
	sanguis::client::gui::menu::callbacks::connect const &_connect,
	sanguis::client::gui::menu::callbacks::cancel_connect const &_cancel_connect,
	sanguis::client::gui::menu::callbacks::quickstart const &_quickstart,
	sanguis::client::gui::menu::callbacks::quit const &_quit
)
:
	connect_(
		_connect
	),
	cancel_connect_(
		_cancel_connect
	),
	quickstart_(
		_quickstart
	),
	quit_(
		_quit
	)
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
