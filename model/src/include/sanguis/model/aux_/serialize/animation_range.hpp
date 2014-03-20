#ifndef SANGUIS_MODEL_AUX__SERIALIZE_ANIMATION_RANGE_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_ANIMATION_RANGE_HPP_INCLUDED

#include <sanguis/model/animation_range_fwd.hpp>
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
animation_range(
	sanguis::model::animation_range const &
);

}
}
}
}

#endif
