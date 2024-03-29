#ifndef SANGUIS_CLIENT_LOAD_MODEL_MAKE_SOUND_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_MAKE_SOUND_HPP_INCLUDED

#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/sounds_cref.hpp>
#include <sanguis/model/optional_animation_sound_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>

namespace sanguis::client::load::model
{

sanguis::client::load::resource::optional_sound make_sound(
    fcppt::log::object &, // NOLINT(google-runtime-references)
    sanguis::model::optional_animation_sound const &,
    sanguis::client::load::resource::sounds_cref);

}

#endif
