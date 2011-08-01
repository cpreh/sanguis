#include "backswing.hpp"
#include "reloading.hpp"
#include "ready.hpp"
#include "../events/poll.hpp"
#include "../events/shoot.hpp"
#include "../events/stop.hpp"
#include "../events/reset.hpp"
#include "../../entities/with_weapon.hpp"

sanguis::server::weapons::states::backswing::backswing(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	cooldown_(
		sanguis::diff_timer::parameters(
			context<
				weapon
			>().diff_clock(),
			context<
				weapon
			>().backswing_time().get()
		)
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
