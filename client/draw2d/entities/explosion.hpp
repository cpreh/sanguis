#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include "base.hpp"
#include "../particle/base_ptr.hpp"
#include "../particle/container.hpp"
#include "../particle/property_map.hpp"
#include "../particle/properties_fwd.hpp"
#include "../sprite/particle/system.hpp"
#include "../funit.hpp"
#include "../../../particle_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class explosion
:
	public base
{
public:
	explosion(
		sprite::particle::system &,
		sprite::point const &pos,
		funit aoe
	);

	~explosion();
private:
	void
	update(
		time_type
	);

	particle::base_ptr
	generate_explosion();

	particle::base_ptr
	generate_particle(
		particle_type::type);

	particle::properties const &
	properties(
		particle_type::type const t) const;
	
	bool may_be_removed() const;

	sprite::point pos_;
	particle::container particles;
	particle::property_map properties_;
	bool ended;
	funit aoe_;
};

}
}
}
}

#endif
