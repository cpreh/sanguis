#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
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
		sanguis::diff_clock const &,
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
		entities::transfer_parameters const &
	);

	void
	do_damage(
		with_health &
	);

	void
	on_update();

	void
	on_remove();

	sanguis::diff_clock const &diff_clock_;

	sanguis::diff_timer slowdown_timer_;

	damage::unit const damage_;

	server::vector const dest_;
};

}
}
}
}

#endif
