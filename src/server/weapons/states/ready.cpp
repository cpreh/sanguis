#include <sanguis/server/weapons/states/ready.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/entities/with_weapon.hpp>

sanguis::server::weapons::states::ready::ready()
{
}

sanguis::server::weapons::states::ready::~ready()
{
}

boost::statechart::result
sanguis::server::weapons::states::ready::react(
	events::shoot const &_event
)
{
	if(
		!context<
			weapon
		>().in_range(
			_event.from(),
			_event.to()
		)
	)
		return discard_event();

	context<
		weapon
	>().init_attack(
		_event.from()
	);

	context<
		weapon
	>().post_event(
		_event
	);

	this->post_event(
		_event
	);

	return transit<castpoint>();
}
