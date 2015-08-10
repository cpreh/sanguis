#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_MAKE_SOUND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_MAKE_SOUND_HPP_INCLUDED

#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/optional_sound.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method_fwd.hpp>
#include <sge/audio/buffer_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

sanguis::client::draw2d::entities::model::optional_sound
make_sound(
	sge::audio::buffer &,
	sanguis::client::sound_manager &,
	sanguis::client::draw2d::sprite::animation::loop_method
);

}
}
}
}
}

#endif
