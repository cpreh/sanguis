#ifndef SANGUIS_COLLISION_WORLD_OPTIONAL_BODY_EXIT_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_OPTIONAL_BODY_EXIT_FWD_HPP_INCLUDED

#include <sanguis/collision/world/body_exit_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef
fcppt::optional<
	sanguis::collision::world::body_exit
>
optional_body_exit;

}
}
}

#endif