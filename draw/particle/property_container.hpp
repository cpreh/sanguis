#ifndef SANGUIS_DRAW_PARTICLE_PROPERTY_CONTAINER_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_PROPERTY_CONTAINER_HPP_INCLUDED

#include "../../particle_type.hpp"
#include <map>

namespace sanguis
{
namespace draw
{
namespace particle
{

class properties;

typedef std::map<
	particle_type::type,
	properties
> property_container;

}
}
}

#endif
