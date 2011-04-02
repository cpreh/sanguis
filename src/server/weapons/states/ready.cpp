#include "ready.hpp"
#include "castpoint.hpp"
#include "../events/shoot.hpp"
#include "../events/poll.hpp"
#include "../events/stop.hpp"
#include "../../entities/with_weapon.hpp"

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
