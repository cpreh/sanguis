#ifndef SANGUIS_SERVER_LOAD_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_LOAD_CALLBACK_HPP_INCLUDED

#include "../load/context_fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<
	load::context const &()
> load_callback;

}
}

#endif
