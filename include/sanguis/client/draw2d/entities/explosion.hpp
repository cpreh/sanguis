#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/particle/base_ptr.hpp>
#include <sanguis/client/draw2d/particle/container.hpp>
#include <sanguis/client/draw2d/particle/property_map.hpp>
#include <sanguis/client/draw2d/particle/properties_fwd.hpp>
#include <sanguis/client/draw2d/particle/particle_type.hpp>
#include <sanguis/client/draw2d/sprite/particle/system.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
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
	public entities::own
{
	FCPPT_NONCOPYABLE(
		explosion
	);
public:
	explosion(
		sanguis::diff_clock const &,
		sprite::particle::system &,
		load::model::collection const &,
		sprite::center const &,
		draw2d::aoe
	);

	~explosion();
private:
	// base overrides

	void
	update();

	bool
	may_be_removed() const;

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

	sanguis::diff_clock const &diff_clock_;

	sprite::particle::system &particle_system_;

	load::model::collection const &model_collection_;

	particle::container particles_;

	particle::property_map properties_;

	draw2d::aoe aoe_;

	bool ended_;
};

}
}
}
}

#endif
