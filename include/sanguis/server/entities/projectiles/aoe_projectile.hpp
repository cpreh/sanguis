#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/indeterminate.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/aoe_projectile_type.hpp>
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

class aoe_projectile
:
	public projectile
{
	FCPPT_NONCOPYABLE(
		aoe_projectile
	);
protected:
	aoe_projectile(
		sanguis::diff_clock const &,
		aoe_projectile_type::type,
		server::team::type,
		entities::movement_speed,
		server::dim const &,
		life_time,
		indeterminate::type,
		server::radius,
		server::direction
	);

	~aoe_projectile();

	server::radius const
	aoe() const;
private:
	messages::auto_ptr
	add_message(
		player_id
	) const;

	aoe_projectile_type::type const type_;

	server::radius const aoe_;
};

}
}
}
}

#endif
