#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_MAKE_SOUND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_MAKE_SOUND_HPP_INCLUDED

#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/optional_sound.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method_fwd.hpp>
#include <sge/audio/buffer_ref.hpp>

namespace sanguis::client::draw2d::entities::model
{

sanguis::client::draw2d::entities::model::optional_sound make_sound(
    sge::audio::buffer_ref,
    sanguis::client::sound_manager &, // NOLINT(google-runtime-references)
    sanguis::client::draw2d::sprite::animation::loop_method);

}

#endif
