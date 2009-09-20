#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED

#include "projectile.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class simple_bullet : public projectile {
public:
	simple_bullet(
		server::environment::load_context_ptr,
		team::type team,
		space_unit damage
	);
private:
	void
	do_damage(
		entity &
	);
	
	space_unit const damage;
};

}
}
}
}

#endif
