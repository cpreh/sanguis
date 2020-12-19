#ifndef SANGUIS_COLLISION_WORLD_GHOST_BASE_REF_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_BASE_REF_HPP_INCLUDED

#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

using
ghost_base_ref
=
fcppt::reference<
	sanguis::collision::world::ghost_base
>;

}
}
}

#endif
