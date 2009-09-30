#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED

#include "projectile.hpp"
#include "life_time.hpp"
#include "indeterminate.hpp"
#include "../movement_speed.hpp"
#include "../../team.hpp"
#include "../../dim_type.hpp"
#include "../../space_unit.hpp"
#include "../../../messages/auto_ptr.hpp"
#include "../../../aoe_projectile_type.hpp"

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
protected:
	aoe_projectile(
		aoe_projectile_type::type,
		team::type,
		entities::movement_speed,
		dim_type const &dim,
		life_time,
		indeterminate::type,
		space_unit aoe,
		space_unit direction
	);
	
	space_unit
	aoe() const;
private:
	messages::auto_ptr
	add_message() const;

	aoe_projectile_type::type const type_;

	space_unit const aoe_;
};

}
}
}
}

#endif
