#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED

#include "aoe_projectile.hpp"
#include "../with_health_fwd.hpp"
#include "../../damage/unit.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../direction.hpp"
#include "../../radius.hpp"
#include "../../team.hpp"
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		rocket
	);
public:
	rocket(
		server::environment::load_context &,
		server::team::type team,
		damage::unit,
		server::radius aoe,
		server::direction
	);

	~rocket();
private:
	void
	do_damage(
		with_health &
	);

	void
	on_remove();
	
	damage::unit const damage_;
};

}
}
}
}

#endif
