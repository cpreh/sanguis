#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_PROPERTY_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_PROPERTY_CONTAINER_HPP_INCLUDED

#include "properties_fwd.hpp"
#include "particle_type.hpp"
#include <map>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

typedef std::map<
	particle::particle_type::type,
	particle::properties
> property_container;

}
}
}
}

#endif
