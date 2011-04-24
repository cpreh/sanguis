#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED

#include "../../sprite/rotation_type.hpp"
#include "../../../../time_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

sprite::rotation_type
orientation(
	sanguis::time_type,
	sprite::rotation_type orientation,
	sprite::rotation_type desired_orientation
);

}
}
}
}
}

#endif
