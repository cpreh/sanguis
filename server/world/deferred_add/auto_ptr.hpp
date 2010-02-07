#ifndef SANGUIS_SERVER_WORLD_DEFERRED_ADD_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_DEFERRED_ADD_AUTO_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace world
{
namespace deferred_add
{

typedef fcppt::auto_ptr<
	object
> auto_ptr;

}
}
}
}

#endif
