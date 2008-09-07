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
		pos_type const& center,
		team::type team,
		space_unit damage);
private:
	entity_type::type type() const;

	void do_hit(
		hit_vector const &target);

	messages::space_unit damage;
};

}
}
}
}

#endif
