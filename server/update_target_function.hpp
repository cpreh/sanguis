#ifndef SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED

#include "entities/base_fwd.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (
		entities::base &
	)
> update_target_function;

}
}

#endif
