#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_OBJECT_HPP_INCLUDED

#include <sanguis/client/gui/menu/callbacks/cancel_connect.hpp>
#include <sanguis/client/gui/menu/callbacks/connect.hpp>
#include <sanguis/client/gui/menu/callbacks/object_fwd.hpp>
#include <sanguis/client/gui/menu/callbacks/quickstart.hpp>
#include <sanguis/client/gui/menu/callbacks/quit.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace menu
{
namespace callbacks
{

class object
{
	FCPPT_NONASSIGNABLE(
		object
	);
public:
	object(
		sanguis::client::gui::menu::callbacks::connect const &,
		sanguis::client::gui::menu::callbacks::cancel_connect const &,
		sanguis::client::gui::menu::callbacks::quickstart const &,
		sanguis::client::gui::menu::callbacks::quit const &
	);

	sanguis::client::gui::menu::callbacks::connect const &
	connect() const;

	sanguis::client::gui::menu::callbacks::cancel_connect const &
	cancel_connect() const;

	sanguis::client::gui::menu::callbacks::quickstart const &
	quickstart() const;

	sanguis::client::gui::menu::callbacks::quit const &
	quit() const;
private:
	sanguis::client::gui::menu::callbacks::connect const connect_;

	sanguis::client::gui::menu::callbacks::cancel_connect const cancel_connect_;

	sanguis::client::gui::menu::callbacks::quickstart const quickstart_;

	sanguis::client::gui::menu::callbacks::quit const quit_;
};

}
}
}
}
}

#endif
