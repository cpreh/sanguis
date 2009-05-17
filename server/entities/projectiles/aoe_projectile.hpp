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
		server::environment const &,
		pos_type const &center,
		space_unit angle,
		team::type,
		property_map const &,
		dim_type const &dim,
		optional_life_time const &lifetime,
		indeterminate::type,
		space_unit aoe);
	
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
