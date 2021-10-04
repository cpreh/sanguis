#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_SOUND_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_ANIMATION_SOUND_HPP_INCLUDED

#include <sanguis/model/optional_animation_sound_fwd.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sanguis::model::impl::serialize
{

fcppt::optional::object<
	sge::parse::json::member
>
animation_sound(
	sanguis::model::optional_animation_sound const &
);

}

#endif
