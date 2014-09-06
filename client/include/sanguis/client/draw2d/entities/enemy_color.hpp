#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_COLOR_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sge/image/color/any/object.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

sge::image::color::any::object
enemy_color(
	sanguis::enemy_kind
);

}
}
}
}

#endif
