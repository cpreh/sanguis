#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/model/animation_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis::model::impl::deserialize
{

sanguis::model::animation_map
animation_map(
	sge::parse::json::object const &
);

}

#endif
