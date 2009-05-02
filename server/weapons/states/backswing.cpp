#include "backswing.hpp"
#include "reloading.hpp"
#include "ready.hpp"
#include "../events/poll.hpp"
#include "../events/shoot.hpp"
#include "../../entities/entity_with_weapon.hpp"

sanguis::server::weapons::states::backswing::backswing(
	my_context ctx)
:
	my_base(ctx),
	diff_clock_(),
	cooldown(
		context<
			weapon
		>().backswing_time(),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{}

boost::statechart::result
sanguis::server::weapons::states::backswing::react(
	events::poll const &e)
{
	diff_clock_.update(
		e.time() * context<weapon>().ias()
	);

	if(!cooldown.expired())
		return discard_event();
	
	context<weapon>().use_magazine_item();

	e.owner().attack_ready();

	post_event(e);

	if(context<weapon>().magazine_empty())
	{
		e.owner().start_reloading();
		return transit<reloading>();
	}
	return transit<ready>();
}
