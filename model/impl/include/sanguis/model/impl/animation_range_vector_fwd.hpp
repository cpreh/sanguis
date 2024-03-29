#ifndef SANGUIS_MODEL_IMPL_ANIMATION_RANGE_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_ANIMATION_RANGE_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/model/animation_index.hpp>
#include <fcppt/math/vector/static_fwd.hpp>

namespace sanguis::model::impl
{

using animation_range_vector = fcppt::math::vector::static_<sanguis::model::animation_index, 2>;

}

#endif
