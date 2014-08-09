#ifndef SANGUIS_CLIENT_CURSOR_AREA_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_AREA_FWD_HPP_INCLUDED

#include <sge/input/cursor/position_unit.hpp>
#include <fcppt/math/box/rect.hpp>


namespace sanguis
{
namespace client
{

typedef
fcppt::math::box::rect<
	sge::input::cursor::position_unit
>
cursor_area;

}
}

#endif
