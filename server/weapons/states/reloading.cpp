#include "reloading.hpp"
#include "ready.hpp"
#include "../events/poll.hpp"
#include "../events/shoot.hpp"
#include "../events/reset.hpp"
#include "../../entities/entity_with_weapon.hpp"

sanguis::server::weapons::states::reloading::reloading(
	my_context ctx)
:
	my_base(ctx),
	diff_clock_(),
	reload_time(
		context<
			weapon
		>().reload_time(),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	events::poll const &e)
{
	diff_clock_.update(
		e.time() * context<weapon>().irs()
	);

	if(!reload_time.expired())
		return discard_event();
	
	context<
		weapon
	>().reset_magazine();

	e.owner().stop_reloading();

	return transit<ready>();
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	events::reset const &)
{
	reload_time.expire();
	
	return discard_event();
}
