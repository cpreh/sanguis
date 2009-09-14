#ifndef SANGUIS_SERVER_UPDATE_SIGHT_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_SIGHT_FUNCTION_HPP_INCLUDED

#include "../entity_id.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<
	void (
		entity_id
	)
> update_sight_function;

}
}

#endif
