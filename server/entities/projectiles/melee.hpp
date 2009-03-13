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
		server::environment const &,
		pos_type const& center,
		team::type team,
		space_unit damage);
private:
	void collision(
		entity &);

	messages::space_unit const damage;
};

}
}
}
}

#endif
