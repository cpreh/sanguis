#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_PROPERTY_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_PROPERTY_CONTAINER_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/properties_fwd.hpp>
#include <sanguis/client/draw2d/particle/particle_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

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
