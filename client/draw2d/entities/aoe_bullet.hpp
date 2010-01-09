#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED

#include "model/parameters_fwd.hpp"
#include "model/object.hpp"
#include "../sprite/particle/system.hpp"
#include "../funit.hpp"
#include <fcppt/function/object.hpp>

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
public:
	aoe_bullet(
		model::parameters const &,
		sprite::particle::system &,
		insert_callback const &,
		fcppt::string const &name,
		funit aoe
	);
private:
	void
	on_decay();

	sprite::particle::system &particle_system_;

	insert_callback const insert;

	funit const aoe;

};

}
}
}
}

#endif
