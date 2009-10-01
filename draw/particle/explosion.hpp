#ifndef SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_EXPLOSION_HPP_INCLUDED

#include "container.hpp"
#include "property_map.hpp"
#include "base_ptr.hpp"
#include "../../particle_type.hpp"
#include <sge/function/object_fwd.hpp>

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
	typedef sge::function::object<
		base_ptr (particle_type::type)
	> callback;

	explosion(
		property_map const &,
		callback const &,
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
