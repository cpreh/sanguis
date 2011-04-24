#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED

#include "model/parameters_fwd.hpp"
#include "model/object.hpp"
#include "../sprite/particle/system.hpp"
#include "../aoe.hpp"
#include "../insert_own_callback.hpp"
#include "../../../load/model/collection_fwd.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class aoe_bullet
:
	public model::object
{
	FCPPT_NONCOPYABLE(
		aoe_bullet
	);
public:
	aoe_bullet(
		model::parameters const &,
		sprite::particle::system &,
		draw2d::insert_own_callback const &,
		fcppt::string const &name,
		draw2d::aoe
	);

	~aoe_bullet();
private:
	void
	on_decay();

	load::model::collection const &model_collection_;

	sprite::particle::system &particle_system_;

	draw2d::insert_own_callback const insert_;

	draw2d::aoe const aoe_;

};

}
}
}
}

#endif
