#ifndef SANGUIS_CLIENT_LOAD_MODEL_MAKE_SOUND_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_MAKE_SOUND_HPP_INCLUDED

#include <sanguis/client/load/model/optional_sound_fwd.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/model/optional_animation_sound_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

sanguis::client::load::model::optional_sound
make_sound(
	sanguis::model::optional_animation_sound const &,
	sanguis::client::load::resource::sounds const &
);

}
}
}
}

#endif
