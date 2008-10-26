#ifndef SANGUIS_LOAD_SOUND_CONTAINER_HPP_INCLUDED
#define SANGUIS_LOAD_SOUND_CONTAINER_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <vector>

namespace sanguis
{
namespace load
{

typedef std::vector<
	sge::audio::file_ptr
> sound_container;

}
}

#endif
