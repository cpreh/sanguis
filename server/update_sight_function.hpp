#ifndef SANGUIS_SERVER_UPDATE_SIGHT_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_SIGHT_FUNCTION_HPP_INCLUDED

#include "../entity_id.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (
		entity_id
	)
> update_sight_function;

}
}

#endif
