#include "backswing.hpp"
#include "reloading.hpp"
#include "ready.hpp"
#include "../events/poll.hpp"
#include "../events/shoot.hpp"
#include "../events/stop.hpp"
#include "../events/reset.hpp"
#include "../../entities/with_weapon.hpp"
#include <fcppt/chrono/duration_arithmetic.hpp>

sanguis::server::weapons::states::backswing::backswing(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	diff_clock_(),
	cooldown_(
		context<
			weapon
		>().backswing_time(),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{
}

sanguis::server::weapons::states::backswing::~backswing()
{
}

boost::statechart::result
sanguis::server::weapons::states::backswing::react(
	events::poll const &_event
)
{
	diff_clock_.update(
		_event.time() * context<weapon>().ias()
	);

	if(
		!cooldown_.expired()
	)
		return discard_event();
	
	context<weapon>().use_magazine_item();

	_event.owner().attack_ready();

	this->post_event(
		_event
	);

	if(
		context<weapon>().magazine_empty()
	)
	{
		_event.owner().start_reloading();

		context<weapon>().magazine_exhausted();

		return transit<reloading>();
	}

	return transit<ready>();
}
