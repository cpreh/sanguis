#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include "projectile.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class melee : public projectile {
public:
	melee(
		environment const &,
		armor_array const &,
		messages::pos_type const& pos,
		team::type team,
		messages::space_unit damage);
private:
	entity_type::type type() const;
	messages::dim_type dim() const;

	void do_hit(
		entity &target);

	messages::space_unit damage;
};

}
}
}
}

#endif
