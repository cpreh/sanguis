#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED

#include "pickup.hpp"
#include "../entity_with_weapon_fwd.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../health_type.hpp"
#include "../../team.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class health : public pickup {
public:
	health(
		server::environment::load_context_ptr,
		team::type team,
		health_type amount
	);
private:
	void
	do_pickup(
		entity_with_weapon &receiver
	);

	health_type const amount;
};

}
}
}
}

#endif
