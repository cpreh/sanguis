#ifndef SANGUIS_MODEL_CELL_AREA_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_CELL_AREA_FWD_HPP_INCLUDED

#include <sanguis/model/cell_size_unit.hpp>
#include <fcppt/math/box/rect_fwd.hpp>


namespace sanguis::model
{

using
cell_area
=
fcppt::math::box::rect<
	sanguis::model::cell_size_unit
>;

}

#endif
