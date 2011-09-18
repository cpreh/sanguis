#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_PARTICLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_PARTICLE_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/base_ptr.hpp>
#include <sanguis/client/draw2d/particle/particle_type.hpp>
#include <sanguis/client/draw2d/particle/properties_fwd.hpp>
#include <sanguis/client/draw2d/sprite/particle/system.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/load/model/animation/context_ptr.hpp>
#include <sanguis/diff_clock_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

particle::base_ptr
explosion_particle(
	sanguis::diff_clock const &,
	particle::particle_type::type,
	sprite::particle::system &,
	draw2d::aoe,
	particle::properties const &,
	sanguis::load::model::animation::context_ptr
);

}
}
}
}

#endif
