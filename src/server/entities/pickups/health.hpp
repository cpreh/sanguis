#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED

#include "pickup.hpp"
#include "../base_fwd.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../health.hpp"
#include "../../team.hpp"
#include "../../../diff_clock_fwd.hpp"
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
	);
public:
	health(
		sanguis::diff_clock const &,
		server::environment::load_context &,
		team::type team,
		server::health amount
	);

	~health();
private:
	void
	do_pickup(
		base &receiver
	);

	server::health const amount_;
};

}
}
}
}

#endif
