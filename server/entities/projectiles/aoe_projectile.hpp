#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED

#include "projectile.hpp"
#include "../../../aoe_projectile_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class aoe_projectile : public projectile {
protected:
	aoe_projectile(
		aoe_projectile_type::type,
		server::environment::load_context_ptr,
		team::type,
		property_map const &,
		dim_type const &dim,
		life_time,
		indeterminate::type,
		space_unit aoe
	);
	
	space_unit aoe() const;
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
