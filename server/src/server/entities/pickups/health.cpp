#include <sanguis/pickup_type.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/cast/try_dynamic.hpp>


sanguis::server::entities::pickups::health::health(
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::health const _amount
)
:
	sanguis::server::entities::pickups::pickup(
		sanguis::pickup_type::health,
		_load_context,
		_team
	),
	amount_(
		_amount
	)
{
}

sanguis::server::entities::pickups::health::~health()
{
}

bool
sanguis::server::entities::pickups::health::do_pickup(
	sanguis::server::entities::base &_receiver
)
{
	return
		fcppt::maybe(
			fcppt::cast::try_dynamic<
				sanguis::server::entities::with_health &
			>(
				_receiver
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				sanguis::server::entities::with_health &_with_health
			)
			{
				sanguis::server::entities::property::add(
					_with_health.health(),
					amount_.get()
				);

				return
					true;
			}
		);
}
