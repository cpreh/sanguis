#ifndef SANGUIS_MODEL_AUX__SERIALIZE_ANIMATION_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_ANIMATION_MAP_HPP_INCLUDED

#include <sanguis/model/animation_map.hpp>
#include <sge/parse/json/member.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace serialize
{

sge::parse::json::member
animation_map(
	sanguis::model::animation_map const &
);

}
}
}
}

#endif
