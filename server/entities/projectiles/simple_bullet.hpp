#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SIMPLE_BULLET_HPP_INCLUDED

#include "projectile.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class simple_bullet : public projectile {
public:
	simple_bullet(
		environment const &,
		armor_array const &,
		pos_type const &center,
		space_unit angle,
		team::type team,
		space_unit damage);
private:
	entity_type::type type() const;

	void do_hit(
		entity &target);

	space_unit damage;
};

}
}
}
}

#endif
