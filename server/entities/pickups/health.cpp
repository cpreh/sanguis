#include "health.hpp"
#include "../entity_with_weapon.hpp"
#include <sge/optional_impl.hpp>

sanguis::server::entities::pickups::health::health(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	health_type const amount
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
	with_weapon &receiver
)
{
	receiver.health(
		receiver.health() + amount
	);
}
