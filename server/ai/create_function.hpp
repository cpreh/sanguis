#ifndef SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../entities/with_ai_fwd.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

// TODO: we will have to return an auto_ptr here
typedef sge::function::object<
	base * (
		entities::with_ai &
	)
> create_function;

}
}
}

#endif