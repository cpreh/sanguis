#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_GRENADE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
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
	public sanguis::server::entities::projectiles::aoe_projectile
{
	FCPPT_NONCOPYABLE(
		grenade
	);
public:
	grenade(
		sanguis::diff_clock const &,
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::damage::unit,
		sanguis::server::radius aoe,
		sanguis::server::vector const &dest,
		sanguis::server::direction
	);

	~grenade();
private:
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	void
	do_damage(
		sanguis::server::entities::with_health &
	)
	override;

	void
	update()
	override;

	void
	remove()
	override;

	sanguis::diff_clock const &diff_clock_;

	sanguis::diff_timer slowdown_timer_;

	sanguis::server::damage::unit const damage_;

	sanguis::server::vector const dest_;
};

}
}
}
}

#endif
