#ifndef SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED

#include "entities/with_body_fwd.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::function::object<
	void (
		entities::with_body &
	)
> update_target_function;

}
}

#endif
