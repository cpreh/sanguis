#ifndef SANGUIS_MODEL_CELL_AREA_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_CELL_AREA_FWD_HPP_INCLUDED

#include <sanguis/model/cell_size_unit.hpp>
#include <fcppt/math/box/rect_fwd.hpp>


namespace sanguis
{
namespace model
{

typedef
fcppt::math::box::rect<
	sanguis::model::cell_size_unit
>
cell_area;

}
}

#endif
