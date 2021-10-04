#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUICKSTART_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUICKSTART_HPP_INCLUDED

#include <alda/net/port.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::client::gui::menu::callbacks
{

using
quickstart
=
fcppt::function<
	void(
		alda::net::port
	)
>;

}

#endif
