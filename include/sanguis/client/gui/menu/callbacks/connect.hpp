#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_CONNECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_CONNECT_HPP_INCLUDED

#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


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

typedef std::function<
	void (
		alda::net::host const &,
		alda::net::port const &
	)
> connect;

}
}
}
}
}

#endif
