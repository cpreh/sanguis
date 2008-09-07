#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED

#include "projectile.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class rocket : public projectile {
public:
	rocket(
		environment const &,
		pos_type const &center,
		space_unit angle,
		team::type team,
		space_unit damage);
private:
	entity_type::type type() const;
		
	void do_hit(
		entity &target);
	void do_die();
	
	space_unit damage;
};

}
}
}
}

#endif
