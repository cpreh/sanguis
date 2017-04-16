#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_RANGE_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_RANGE_HPP_INCLUDED

#include <sanguis/model/animation_range_fwd.hpp>
#include <sge/parse/json/member.hpp>


namespace sanguis
{
namespace model
{
namespace impl
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
