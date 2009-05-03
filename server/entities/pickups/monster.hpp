#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED

#include "pickup.hpp"
#include "../../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class monster : public pickup {
public:
	monster(
		server::environment const &,
		pos_type const &center,
		team::type,
		enemy_type::type);
private:
	void do_pickup(
		entity_with_weapon &receiver);
	
	enemy_type::type const etype;
};

}
}
}
}

#endif
