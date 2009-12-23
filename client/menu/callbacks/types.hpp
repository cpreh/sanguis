#ifndef SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED

#include <fcppt/function/object_fwd.hpp>
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

typedef fcppt::function::object<
	void (sge::string const &,sge::string const &)
> connect;

typedef fcppt::function::object<
	void ()
> cancel_connect;

typedef fcppt::function::object<
	void ()
> start_server;

typedef fcppt::function::object<
	void ()
> quit;

}
}
}
}

#endif // SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED
