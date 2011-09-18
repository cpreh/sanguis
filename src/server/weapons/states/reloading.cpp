#include <sanguis/server/weapons/states/reloading.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/events/reset.hpp>
#include <sanguis/server/entities/with_weapon.hpp>

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
