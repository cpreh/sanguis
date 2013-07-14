#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/projectiles/damage_per_pulse.hpp>
#include <sanguis/server/entities/projectiles/pulse_time.hpp>
#include <sanguis/server/entities/projectiles/pulses.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class aoe_damage
:
	public sanguis::server::entities::with_auras,
	private sanguis::server::entities::center_ghost
{
	FCPPT_NONCOPYABLE(
		aoe_damage
	);
public:
	aoe_damage(
		sanguis::diff_clock const &,
		sanguis::server::team,
		sanguis::server::radius,
		sanguis::server::entities::projectiles::damage_per_pulse,
		sanguis::server::entities::projectiles::pulses,
		sanguis::server::entities::projectiles::pulse_time const &,
		sanguis::server::damage::array const &damage_values
	);

	~aoe_damage();
private:
	bool
	dead() const
	override;

	sanguis::server::team
	team() const
	override;

	sanguis::server::team const team_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
