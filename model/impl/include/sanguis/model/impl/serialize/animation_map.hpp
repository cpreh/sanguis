#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/model/animation_map.hpp>
#include <sge/parse/json/member.hpp>


namespace sanguis::model::impl::serialize
{

sge::parse::json::member
animation_map(
	sanguis::model::animation_map const &
);

}

#endif
