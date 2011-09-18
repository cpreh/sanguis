#ifndef SANGUIS_SERVER_COLLISION_GHOST_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/collision/ghost_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef fcppt::unique_ptr<
	collision::ghost
> ghost_unique_ptr;

}
}
}

#endif
