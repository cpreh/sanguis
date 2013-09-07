#ifndef SANGUIS_COLLISION_WORLD_BODY_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/collision/world/body_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef
std::unique_ptr<
	sanguis::collision::world::body
>
body_unique_ptr;

}
}
}

#endif
