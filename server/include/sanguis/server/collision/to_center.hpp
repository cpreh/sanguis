#ifndef SANGUIS_SERVER_COLLISION_TO_CENTER_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_CENTER_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/server/center_fwd.hpp>


namespace sanguis::server::collision
{

sanguis::collision::center
to_center(
	sanguis::server::center const &
);

}

#endif
