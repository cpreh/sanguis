#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED

#include "aoe_projectile.hpp"
#include "../with_health_fwd.hpp"
#include "../../damage/unit.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../direction.hpp"
#include "../../vector.hpp"
#include "../../radius.hpp"
#include "../../team.hpp"
#include "../../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class grenade
:
	public aoe_projectile
{
	FCPPT_NONCOPYABLE(
		grenade
	);
public:
	grenade(
		server::environment::load_context &,
		server::team::type,
		damage::unit,
		server::radius aoe,
		server::vector const &dest,
		server::direction
	);

	~grenade();
private:
	void
	on_transfer(
		collision::global_groups const &,
		collision::create_parameters const &
	);

	void
	do_damage(
		with_health &
	);
	
	void
	on_update(
		time_type
	);
	
	void
	on_die();
	
	diff_clock diff_clock_;

	sge::time::timer slowdown_time_;

	damage::unit const damage_;

	server::vector const dest_;
};

}
}
}
}

#endif
