#ifndef SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_PTR_HPP_INCLUDED

#include "load_context_fwd.hpp"
#include <fcppt/shared_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace environment
{

typedef fcppt::shared_ptr<
	load_context
> load_context_ptr;

}
}
}

#endif
