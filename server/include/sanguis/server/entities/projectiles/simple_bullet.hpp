#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED

#include <sanguis/server/direction.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
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

class simple_bullet
:
	public sanguis::server::entities::projectiles::projectile
{
	FCPPT_NONCOPYABLE(
		simple_bullet
	);
public:
	simple_bullet(
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::damage::unit,
		sanguis::server::direction
	);

	~simple_bullet()
	override;
private:
	void
	do_damage(
		sanguis::server::entities::with_health &
	)
	override;

	sanguis::server::damage::unit const damage_;
};

}
}
}
}

#endif
