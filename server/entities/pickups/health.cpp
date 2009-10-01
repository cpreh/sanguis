#include "health.hpp"
#include "../with_health.hpp"
#include <sge/optional_impl.hpp>

sanguis::server::entities::pickups::health::health(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	entities::health_type const amount
)
:
	pickup(
		pickup_type::health,
		load_context,
		team_,
		optional_dim()
	),
	amount(amount)
{}

void
sanguis::server::entities::pickups::health::do_pickup(
	base &receiver
)
{
	with_health &with_health_(
		dynamic_cast<
			with_health &
		>(
			receiver
		)
	);
	
	// TODO:
	
	with_health_.health().current(
		with_health_.health().current() + amount
	);
}
