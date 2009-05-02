#include "ready.hpp"
#include "castpoint.hpp"
#include "../events/shoot.hpp"
#include "../events/poll.hpp"

boost::statechart::result
sanguis::server::weapons::states::ready::react(
	events::shoot const &e)
{
	context<
		weapon
	>().on_init_attack(
		e.from()
	);

	context<
		weapon
	>().post_event(
		e
	);

	return transit<castpoint>();
}
