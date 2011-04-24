#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_EXPLOSION_HPP_INCLUDED

#include "base_ptr.hpp"
#include "container.hpp"
#include "depth.hpp"
#include "particle_type.hpp"
#include "property_map.hpp"
#include "rotation.hpp"
#include "rotation_speed.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

// explosion is a container spawning three generators
class explosion
:
	public particle::container
{
	FCPPT_NONCOPYABLE(
		explosion
	);
public:
	typedef fcppt::function::object<
		base_ptr (particle_type::type)
	> callback;

	explosion(
		property_map const &,
		callback const &,
		draw2d::center const &,
		draw2d::speed const &,
		particle::depth,
		particle::rotation,
		particle::rotation_speed
	);

	~explosion();
};

}
}
}
}

#endif
