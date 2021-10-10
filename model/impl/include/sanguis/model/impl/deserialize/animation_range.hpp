#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_RANGE_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_RANGE_HPP_INCLUDED

#include <sanguis/model/animation_range.hpp>
#include <sge/parse/json/object_fwd.hpp>

namespace sanguis::model::impl::deserialize
{

sanguis::model::animation_range animation_range(sge::parse::json::object const &);

}

#endif
