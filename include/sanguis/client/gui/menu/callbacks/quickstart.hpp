#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUICKSTART_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUICKSTART_HPP_INCLUDED

#include <alda/net/port.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
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
	void(
		alda::net::port
	)
> quickstart;

}
}
}
}
}

#endif
