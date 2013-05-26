#ifndef SANGUIS_SERVER_WORLD_MAKE_TRIANGLES_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAKE_TRIANGLES_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sge::projectile::shape::triangle_sequence
make_triangles(
	sanguis::creator::grid const &
);

}
}
}

#endif
