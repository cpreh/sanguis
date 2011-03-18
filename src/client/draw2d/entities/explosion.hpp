#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include "base.hpp"
#include "../particle/base_ptr.hpp"
#include "../particle/container.hpp"
#include "../particle/property_map.hpp"
#include "../particle/properties_fwd.hpp"
#include "../particle/particle_type.hpp"
#include "../sprite/particle/system.hpp"
#include "../funit.hpp"
#include "../../../load/model/collection_fwd.hpp"
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		explosion
	);
public:
	explosion(
		sprite::particle::system &,
		load::model::collection const &,
		sprite::point const &pos,
		funit aoe
	);

	~explosion();
private:
	// base overrides
	
	void
	update(
		time_type
	);

	void
	pos(
		sprite::point const &
	);

	void
	dim(
		sprite::dim const &
	);

	sprite::point const
	center() const;

	particle::base_ptr
	generate_explosion();

	particle::base_ptr
	generate_particle(
		particle::particle_type::type
	);

	particle::properties const &
	properties(
		particle::particle_type::type const t
	) const;
	
	bool
	is_decayed() const;

	sprite::particle::system &particle_system_;

	load::model::collection const &model_collection_;

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
