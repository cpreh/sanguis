#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED

#include "../../sprite/rotation.hpp"
#include "../../../../time_delta_fwd.hpp"

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

sprite::rotation
orientation(
	sanguis::time_delta const &,
	sprite::rotation orientation,
	sprite::rotation desired_orientation
);

}
}
}
}
}

#endif
