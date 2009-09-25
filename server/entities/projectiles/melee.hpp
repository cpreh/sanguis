#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include "projectile.hpp"
#include "../with_health.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../damage/unit.hpp"
#include "../../team.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class melee
:
	public projectile
{
public:
	melee(
		server::environment::load_context_ptr,
		team::type team,
		damage::unit
	);
private:
	void
	do_damage(
		with_health &
	);

	damage::unit const damage_;
};

}
}
}
}

#endif
