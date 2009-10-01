#ifndef SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED

#include <sge/function/object_fwd.hpp>
#include <sge/string.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
namespace callbacks
{

// TODO: split this!

typedef sge::function::object<
	void (sge::string const &,sge::string const &)
> connect;

typedef sge::function::object<
	void ()
> cancel_connect;

typedef sge::function::object<
	void ()
> start_server;

typedef sge::function::object<
	void ()
> quit;

}
}
}
}

#endif // SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED
