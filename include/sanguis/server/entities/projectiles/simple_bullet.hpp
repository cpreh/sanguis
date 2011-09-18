#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
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
	public projectile
{
	FCPPT_NONCOPYABLE(
		simple_bullet
	);
public:
	simple_bullet(
		sanguis::diff_clock const &,
		server::environment::load_context &,
		server::team::type,
		damage::unit,
		server::direction
	);

	~simple_bullet();
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
