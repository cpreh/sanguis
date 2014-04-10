#ifndef SANGUIS_SERVER_COLLISION_GHOST_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/collision/ghost_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

typedef std::unique_ptr<
	sanguis::server::collision::ghost
> ghost_unique_ptr;

}
}
}

#endif
