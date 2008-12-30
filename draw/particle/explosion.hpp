#ifndef SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED

#include "container.hpp"
#include "property_map.hpp"
#include "../../particle_type.hpp"

namespace sanguis
{
namespace draw
{
namespace particle
{

// explosion is a container spawning three generators
class explosion : public container
{
	public:
	typedef boost::function<
		base_ptr (particle_type::type)
	> callback;

	explosion(
		property_map const &,
		callback,
		point const &pos,
		point const &speed,
		depth_type,
		rotation_type,
		rotation_type,
		draw::environment const &);
};

}
}
}

#endif
