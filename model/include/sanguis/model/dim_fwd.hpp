#ifndef SANGUIS_MODEL_DIM_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_DIM_FWD_HPP_INCLUDED

#include <sanguis/model/cell_size_unit.hpp>
#include <fcppt/math/dim/static_fwd.hpp>


namespace sanguis
{
namespace model
{

typedef
fcppt::math::dim::static_<
	sanguis::model::cell_size_unit,
	2
>
dim;

}
}

#endif
