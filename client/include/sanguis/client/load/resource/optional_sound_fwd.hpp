#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_OPTIONAL_SOUND_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_OPTIONAL_SOUND_FWD_HPP_INCLUDED

#include <sge/audio/buffer_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

using
optional_sound
=
fcppt::optional::reference<
	sge::audio::buffer
>;

}
}
}
}

#endif
