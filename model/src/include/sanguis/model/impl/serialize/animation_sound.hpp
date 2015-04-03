#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_SOUND_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_SOUND_HPP_INCLUDED

#include <sanguis/model/optional_animation_sound_fwd.hpp>
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
animation_sound(
	sanguis::model::optional_animation_sound const &
);

}
}
}
}

#endif
