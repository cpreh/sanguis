#ifndef SANGUIS_SERVER_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

typedef fcppt::unique_ptr<
	object
> object_unique_ptr;

}
}
}

#endif
