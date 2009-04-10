#ifndef SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED

#include <sge/string.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
namespace callbacks
{
typedef boost::function<
	void (sge::string const &,sge::string const &)
> connect;

typedef boost::function<
	void ()
> cancel_connect;

typedef boost::function<
	void ()
> start_server;

}
}
}
}

#endif // SANGUIS_CLIENT_MENU_CALLBACKS_TYPES_HPP_INCLUDED
