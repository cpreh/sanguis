#ifndef SANGUIS_COLLISION_AUX_WORLD_SIMPLE_BODY_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_SIMPLE_BODY_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/collision/aux/world/simple/body_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{
namespace world
{
namespace simple
{

typedef
std::unique_ptr<
	sanguis::collision::aux::world::simple::body
>
body_unique_ptr;

}
}
}
}
}

#endif
