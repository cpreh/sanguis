#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_DELAY_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_DELAY_HPP_INCLUDED

#include <sanguis/model/optional_animation_delay_fwd.hpp>
#include <sge/parse/json/optional_member.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{
namespace serialize
{

sge::parse::json::optional_member
animation_delay(
	sanguis::model::optional_animation_delay const &
);

}
}
}
}

#endif
