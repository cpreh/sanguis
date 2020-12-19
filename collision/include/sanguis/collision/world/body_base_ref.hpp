#ifndef SANGUIS_COLLISION_WORLD_BODY_BASE_REF_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_BASE_REF_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

using
body_base_ref
=
fcppt::reference<
	sanguis::collision::world::body_base
>;

}
}
}

#endif
