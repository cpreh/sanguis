#ifndef SANGUIS_MODEL_DIM_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_DIM_FWD_HPP_INCLUDED

#include <sanguis/model/cell_size_unit.hpp>
#include <fcppt/math/dim/static_fwd.hpp>

namespace sanguis::model
{

using dim = fcppt::math::dim::static_<sanguis::model::cell_size_unit, 2>;

}

#endif
