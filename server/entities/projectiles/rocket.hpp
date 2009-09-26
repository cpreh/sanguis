#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED

#include "aoe_projectile.hpp"
#include "../with_health_fwd.hpp"
#include "../../damage/unit.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../team.hpp"
#include "../../space_unit.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class rocket
:
	public aoe_projectile
{
public:
	rocket(
		server::environment::load_context_ptr,
		team::type team,
		damage::unit,
		space_unit aoe,
		space_unit angle
	);
private:
	void
	do_damage(
		with_health &
	);

	void
	on_die();
	
	damage::unit const damage_;
};

}
}
}
}

#endif
