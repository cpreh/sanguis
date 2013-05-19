#ifndef SANGUIS_SERVER_WORLD_CREATE_STATIC_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CREATE_STATIC_BODY_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sge/projectile/body/object_unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sge::projectile::body::object_unique_ptr
create_static_body(
	sanguis::creator::grid const &
);

}
}
}

#endif
