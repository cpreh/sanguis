#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_MONSTER_HPP_INCLUDED

#include "pickup.hpp"
#include "../base_fwd.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../team.hpp"
#include "../../../friend_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class monster
:
	public pickup
{
	FCPPT_NONCOPYABLE(
		monster
	)
public:
	monster(
		server::environment::load_context_ptr,
		team::type,
		friend_type::type
	);

	~monster();
private:
	void
	do_pickup(
		base &receiver
	);
	
	friend_type::type const ftype_;
};

}
}
}
}

#endif
