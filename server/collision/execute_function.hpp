#ifndef SANGUIS_SERVER_COLLISION_EXECUTE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_EXECUTE_FUNCTION_HPP_INCLUDED

#include "base_fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef boost::function<
	void (
		collision::base &,
		collision::base &
	)
> execute_function;

}
}
}

#endif
