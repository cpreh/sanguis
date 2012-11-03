#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::weapons::states::ready::ready()
{
}

sanguis::server::weapons::states::ready::~ready()
{
}

boost::statechart::result
sanguis::server::weapons::states::ready::react(
	sanguis::server::weapons::events::shoot const &_event
)
{
	if(
		!this->context<
			sanguis::server::weapons::weapon
		>().in_range(
			_event.from(),
			_event.to()
		)
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::weapons::weapon
	>().init_attack(
		_event.from()
	);

	this->context<
		sanguis::server::weapons::weapon
	>().post_event(
		_event
	);

	this->post_event(
		_event
	);

	return
		this->transit<
			sanguis::server::weapons::states::castpoint
		>();
}
