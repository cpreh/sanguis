#include "reloading.hpp"
#include "ready.hpp"
#include "../events/poll.hpp"
#include "../events/shoot.hpp"
#include "../events/stop.hpp"
#include "../events/reset.hpp"
#include "../../entities/with_weapon.hpp"

sanguis::server::weapons::states::reloading::reloading(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	reload_time_(
		sanguis::diff_timer::parameters(
			context<
				weapon
			>().diff_clock(),
			context<
				weapon
			>().reload_time().get()
		)
	)
{
}

sanguis::server::weapons::states::reloading::~reloading()
{
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	events::poll const &_event
)
{
	if(
		!reload_time_.expired()
	)
		return discard_event();

	context<
		weapon
	>().reset_magazine();

	_event.owner().stop_reloading();

	return transit<ready>();
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	events::stop const &
)
{
	reload_time_.reset();

	return discard_event();
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	events::reset const &
)
{
	reload_time_.expired(
		true
	);

	return discard_event();
}
