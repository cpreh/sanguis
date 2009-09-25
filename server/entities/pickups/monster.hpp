#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED

#include "pickup.hpp"
#include "../with_weapon_fwd.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../team.hpp"
#include "../../../friend_type.hpp"

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
		server::environment::load_context_ptr,
		team::type,
		friend_type::type
	);
private:
	void
	do_pickup(
		with_weapon &receiver
	);
	
	friend_type::type const ftype;
};

}
}
}
}

#endif
