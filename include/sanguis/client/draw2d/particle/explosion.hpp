#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_EXPLOSION_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/container.hpp>
#include <sanguis/client/draw2d/particle/depth.hpp>
#include <sanguis/client/draw2d/particle/explosion_callback.hpp>
#include <sanguis/client/draw2d/particle/property_map.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <sanguis/client/draw2d/particle/rotation_speed.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/diff_clock_fwd.hpp>

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
	explosion(
		sanguis::diff_clock const &,
		particle::property_map const &,
		particle::explosion_callback const &,
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
