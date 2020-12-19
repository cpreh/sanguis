#ifndef SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/tree/base_unique_ptr.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

using
create_function
=
fcppt::function<
	sanguis::server::ai::tree::base_unique_ptr (
		sanguis::server::ai::context_ref
	)
>;

}
}
}

#endif
