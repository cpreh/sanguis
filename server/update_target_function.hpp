#ifndef SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED

#include "entities/entity_fwd.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<
	void (
		entities::entity &
	)
> update_target_function;

}
}

#endif
