#ifndef SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED

#include "container.hpp"
#include "../../particle_type.hpp"

namespace sanguis
{
namespace draw
{
namespace particle
{

struct properties;

// explosion is a container spawning three generators
class explosion : public container
{
	public:
	typedef boost::function<
		base_ptr (particle_type::type)
	> callback;

	explicit explosion(
		properties const &,
		callback,
		point const &pos,
		point const &speed,
		depth_type,
		rotation_type,
		rotation_type);
};

}
}
}

#endif
