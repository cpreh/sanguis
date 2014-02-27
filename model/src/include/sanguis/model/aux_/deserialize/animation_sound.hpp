#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_ANIMATION_SOUND_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_ANIMATION_SOUND_HPP_INCLUDED

#include <sanguis/model/optional_animation_sound.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::optional_animation_sound
animation_sound(
	sge::parse::json::object const &
);

}
}
}
}

#endif
