#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_OBJECT_HPP_INCLUDED

#include <sanguis/client/gui/menu/callbacks/connect.hpp>
#include <sanguis/client/gui/menu/callbacks/cancel_connect.hpp>
#include <sanguis/client/gui/menu/callbacks/quickstart.hpp>
#include <sanguis/client/gui/menu/callbacks/quit.hpp>
#include <fcppt/function/object.hpp>
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

struct object
{
	FCPPT_NONASSIGNABLE(
		object
	);
public:
	object(
		callbacks::connect const &,
		callbacks::cancel_connect const &,
		callbacks::quickstart const &,
		callbacks::quit const &
	);

	callbacks::connect const &
	connect() const;

	callbacks::cancel_connect const &
	cancel_connect() const;

	callbacks::quickstart const &
	quickstart() const;

	callbacks::quit const &
	quit() const;
private:
	callbacks::connect const connect_;

	callbacks::cancel_connect const cancel_connect_;

	callbacks::quickstart const quickstart_;

	callbacks::quit const quit_;
};

}
}
}
}
}

#endif
