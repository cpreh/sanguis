#ifndef SANGUIS_SERVER_LOAD_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_LOAD_CALLBACK_HPP_INCLUDED

#include <boost/function.hpp>

namespace sanguis
{
namespace load
{
class context;
}
namespace server
{

typedef boost::function<
	load::context const &()
> load_callback;

}
}

#endif
