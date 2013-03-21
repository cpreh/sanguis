#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_POINT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_POINT_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/vector.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef sge::sprite::types::vector<
	sanguis::client::draw2d::sprite::type_choices
>::type point;

}
}
}
}

#endif
