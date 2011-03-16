#include "health.hpp"
#include "../with_health.hpp"
#include "../property/add.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::entities::pickups::health::health(
	server::environment::load_context_ptr const _load_context,
	team::type const _team,
	entities::health_type const _amount
)
:
	pickup(
		pickup_type::health,
		_load_context,
		_team,
		optional_dim()
	),
	amount_(_amount)
{
}

sanguis::server::entities::pickups::health::~health()
{
}

void
sanguis::server::entities::pickups::health::do_pickup(
	base &_receiver
)
{
	entities::with_health &with_health(
		dynamic_cast<
			entities::with_health &
		>(
			_receiver
		)
	);
	
	entities::property::add(
		with_health.health(),
		amount_.get()
	);
}
