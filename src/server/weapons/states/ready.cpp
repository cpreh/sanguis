#include <sanguis/weapon_status.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/castpoint_parameters.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::weapons::states::ready::ready()
{
}

sanguis::server::weapons::states::ready::~ready()
{
}

boost::statechart::result
sanguis::server::weapons::states::ready::react(
	sanguis::server::weapons::events::shoot const &_event
)
{
	sanguis::server::entities::with_weapon &from(
		_event.from()
	);

	sanguis::server::weapons::optional_target const target(
		from.target()
	);

	if(
		!target
		||
		!this->context<
			sanguis::server::weapons::weapon
		>().in_range(
			from,
			*target
		)
	)
		return
			this->discard_event();

	from.weapon_status(
		sanguis::weapon_status::attacking,
		this->context<
			sanguis::server::weapons::weapon
		>()
	);

	return
		this->transit<
			sanguis::server::weapons::states::castpoint
		>(
			sanguis::server::weapons::states::castpoint_parameters(
				from.ias()
			)
		);
}
