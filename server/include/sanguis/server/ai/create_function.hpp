#ifndef SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/ai/unique_ptr.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

typedef std::function<
	sanguis::server::ai::unique_ptr (
		sanguis::server::entities::with_ai &
	)
> create_function;

}
}
}

#endif
