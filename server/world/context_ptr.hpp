#ifndef SANGUIS_SERVER_WORLD_CONTEXT_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_PTR_HPP_INCLUDED

#include "context_fwd.hpp"
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

typedef sge::shared_ptr<
	context
> context_ptr;

}
}
}

#endif
