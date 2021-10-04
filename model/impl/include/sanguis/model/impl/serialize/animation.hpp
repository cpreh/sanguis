#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_HPP_INCLUDED

#include <sanguis/model/animation_fwd.hpp>
#include <sge/parse/json/object.hpp>


namespace sanguis::model::impl::serialize
{

sge::parse::json::object
animation(
	sanguis::model::animation const &
);

}

#endif
