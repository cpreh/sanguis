#ifndef SANGUIS_SERVER_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_PROJECTILES_MELEE_HPP_INCLUDED

#include "projectile.hpp"

namespace sanguis
{
namespace server
{
namespace projectiles
{

class melee : public projectile {
public:
	melee(
		messages::pos_type const& pos,
		messages::space_unit angle,
		team::type team,
		messages::space_unit damage);
private:
	void do_hit(entity &target);
	messages::space_unit damage;
};

}
}
}

#endif
