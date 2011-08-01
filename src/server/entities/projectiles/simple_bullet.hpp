#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED

#include "projectile.hpp"
#include "../with_health_fwd.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../damage/unit.hpp"
#include "../../direction.hpp"
#include "../../team.hpp"
#include "../../../diff_clock_fwd.hpp"
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
