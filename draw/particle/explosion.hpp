#ifndef SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED

#include "container.hpp"
#include "../settings/fwd.hpp"
#include "../model_type.hpp"

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
	typedef boost::function<base_ptr (model_type::type)> callback;

	explicit explosion(
		settings::object const &,
		callback,
		point const &pos = point::null(),
		point const &speed = point::null(),
		depth_type = depth_type(),
		rotation_type = rotation_type(),
		rotation_type = rotation_type());
};

}
}
}

#endif
