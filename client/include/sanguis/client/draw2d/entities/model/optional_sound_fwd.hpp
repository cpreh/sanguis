#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OPTIONAL_SOUND_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OPTIONAL_SOUND_FWD_HPP_INCLUDED

#include <sge/audio/sound/base_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


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

using
optional_sound
=
fcppt::optional::object<
	sge::audio::sound::base_unique_ptr
>;

}
}
}
}
}

#endif
