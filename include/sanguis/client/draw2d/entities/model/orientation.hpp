#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ORIENTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>


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

sanguis::client::draw2d::sprite::rotation
orientation(
	sanguis::client::draw2d::funit delta,
	sanguis::client::draw2d::sprite::rotation orientation,
	sanguis::client::draw2d::sprite::rotation desired_orientation
);

}
}
}
}
}

#endif
