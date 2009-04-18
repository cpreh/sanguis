#ifndef SANGUIS_CLIENT_CURSOR_SHOW_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_SHOW_CALLBACK_HPP_INCLUDED

#include <boost/function.hpp>

namespace sanguis
{
namespace client
{

typedef boost::function<
	void (bool)
> cursor_show_callback;

}
}

#endif
