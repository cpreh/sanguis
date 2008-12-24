#ifndef SANGUIS_LOAD_PARTICLES_ANIMATON_CONTAINER_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLES_ANIMATON_CONTAINER_HPP_INCLUDED

#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace load
{
namespace particle
{

class animation;

typedef boost::ptr_vector<
	animation
> animation_container;

}
}
}

#endif
