#ifndef SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
#include <sanguis/server/ai/unique_ptr.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

// TODO: we will have to return an auto_ptr here
typedef fcppt::function::object<
	ai::unique_ptr (
		entities::with_ai &
	)
> create_function;

}
}
}

#endif
