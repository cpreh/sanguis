#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_HEALTH_HPP_INCLUDED

#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
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
