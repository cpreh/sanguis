#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::entities::pickups::health::health(
	sanguis::diff_clock const &_diff_clock,
	server::environment::load_context &_load_context,
	team::type const _team,
	server::health const _amount
)
:
	pickup(
		_diff_clock,
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
