#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_RANGE_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_RANGE_HPP_INCLUDED

#include <sanguis/model/animation_range.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{
namespace deserialize
{

sanguis::model::animation_range const
animation_range(
	sge::parse::json::object const &
);

}
}
}
}

#endif
