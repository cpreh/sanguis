#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/pickups/optional_dim.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


sanguis::server::entities::pickups::health::health(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::health const _amount
)
:
	sanguis::server::entities::pickups::pickup(
		_diff_clock,
		sanguis::pickup_type::health,
		_load_context,
		_team,
		sanguis::server::entities::pickups::optional_dim()
	),
	amount_(
		_amount
	)
{
}

sanguis::server::entities::pickups::health::~health()
{
}

void
sanguis::server::entities::pickups::health::do_pickup(
	sanguis::server::entities::base &_receiver
)
{
	sanguis::server::entities::with_health &with_health(
		dynamic_cast<
			sanguis::server::entities::with_health &
		>(
			_receiver
		)
	);

	sanguis::server::entities::property::add(
		with_health.health(),
		amount_.get()
	);
}
