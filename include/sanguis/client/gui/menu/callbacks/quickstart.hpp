#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUICKSTART_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_QUICKSTART_HPP_INCLUDED

#include <alda/net/port.hpp>
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
