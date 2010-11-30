#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED

#include "pickup.hpp"
#include "../base_fwd.hpp"
#include "../health_type.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../team.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class health
:
	public pickup
{
	FCPPT_NONCOPYABLE(
		health
	)
public:
	health(
		server::environment::load_context_ptr,
		team::type team,
		entities::health_type amount
	);

	~health();
private:
	void
	do_pickup(
		base &receiver
	);

	health_type const amount_;
};

}
}
}
}

#endif
