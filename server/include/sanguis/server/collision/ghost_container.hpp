#ifndef SANGUIS_SERVER_COLLISION_GHOST_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_CONTAINER_HPP_INCLUDED

#include <sanguis/server/collision/ghost.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::collision
{

using
ghost_container
=
std::vector<
	sanguis::server::collision::ghost
>;

}

#endif
