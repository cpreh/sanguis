#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_OBJECT_HPP_INCLUDED

#include "connect.hpp"
#include "cancel_connect.hpp"
#include "start_server.hpp"
#include "quit.hpp"
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
		callbacks::start_server const &,
		callbacks::quit const &
	);

	callbacks::connect const &
	connect() const;

	callbacks::cancel_connect const &
	cancel_connect() const;

	callbacks::start_server const &
	start_server() const;

	callbacks::quit const &
	quit() const;
private:
	callbacks::connect const connect_;

	callbacks::cancel_connect const cancel_connect_;

	callbacks::start_server const start_server_;

	callbacks::quit const quit_;
};

}
}
}
}
}

#endif
