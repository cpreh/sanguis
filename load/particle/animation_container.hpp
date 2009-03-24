#ifndef SANGUIS_LOAD_PARTICLES_ANIMATON_CONTAINER_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLES_ANIMATON_CONTAINER_HPP_INCLUDED

#include "animation_fwd.hpp"
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace load
{
namespace particle
{
typedef boost::ptr_vector<
	animation
> animation_container;

}
}
}

#endif
