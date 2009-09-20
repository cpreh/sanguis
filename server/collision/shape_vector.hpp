#ifndef SANGUIS_SERVER_COLLISION_SHAPE_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_SHAPE_VECTOR_HPP_INCLUDED

#include <sge/collision/shapes/base_fwd.hpp>
#include <vector>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef std::vector<
	sge::collision::shapes::base_ptr
> shape_vector;

}
}
}

#endif
