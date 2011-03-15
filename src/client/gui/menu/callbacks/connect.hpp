#ifndef SANGUIS_CLIENT_GUI_MENU_CALLBACKS_CONNECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CALLBACKS_CONNECT_HPP_INCLUDED

#include <fcppt/function/object_fwd.hpp>
#include <fcppt/string.hpp>

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
		fcppt::string const &,
		fcppt::string const &
	)
> connect;

}
}
}
}
}

#endif
