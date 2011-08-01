#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED

#include "../../sprite/rotation.hpp"
#include "../../funit.hpp"

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
	draw2d::funit delta,
	sprite::rotation orientation,
	sprite::rotation desired_orientation
);

}
}
}
}
}

#endif
