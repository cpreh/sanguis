#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include "projectile.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class melee : public projectile {
public:
	melee(
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
