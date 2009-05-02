#include "ready.hpp"
#include "castpoint.hpp"
#include "../events/shoot.hpp"
#include "../events/poll.hpp"
#include "../../entities/entity_with_weapon.hpp"

#include <sge/cerr.hpp>

boost::statechart::result
sanguis::server::weapons::states::ready::react(
	events::shoot const &e)
{
	sge::cerr << "attack ready\n";

	if(
		!context<
			weapon
		>().in_range(
			e.from(),
			e.to()
		)
	)
		return discard_event();
	
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
