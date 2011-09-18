#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_CONNECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_CONNECT_HPP_INCLUDED

#include <sanguis/net/hostname.hpp>
#include <sanguis/net/port.hpp>
#include <fcppt/function/object_fwd.hpp>

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

typedef fcppt::function::object<
	void (
		net::hostname const &,
		net::port const &
	)
> connect;

}
}
}
}
}

#endif
