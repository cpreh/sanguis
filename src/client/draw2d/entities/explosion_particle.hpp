#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_PARTICLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_PARTICLE_HPP_INCLUDED

#include "../particle/base_ptr.hpp"
#include "../particle/particle_type.hpp"
#include "../particle/properties_fwd.hpp"
#include "../sprite/particle/system.hpp"
#include "../aoe.hpp"
#include "../../../load/model/animation/context_ptr.hpp"

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
