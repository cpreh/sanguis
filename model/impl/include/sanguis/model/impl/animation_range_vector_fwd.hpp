#ifndef SANGUIS_MODEL_IMPL_ANIMATION_RANGE_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_ANIMATION_RANGE_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/model/animation_index.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{

typedef
fcppt::math::vector::static_<
	sanguis::model::animation_index,
	2
>
animation_range_vector;

}
}
}

#endif
