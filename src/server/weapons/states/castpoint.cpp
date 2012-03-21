#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::weapons::states::castpoint::castpoint(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	attack_time_(
		sanguis::diff_timer::parameters(
			context<
				weapon
			>().diff_clock(),
			context<
				weapon
			>().cast_point().get()
		)
	),
	attack_dest_()
{
}

sanguis::server::weapons::states::castpoint::~castpoint()
{
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	events::shoot const &_event
)
{
	// TODO: use constructor instead!
	attack_dest_ = _event.to();

	return discard_event();
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	events::poll const &_event
)
{
	if(
		!attack_time_.expired()
	)
		return discard_event();

	context<
		weapon
	>().do_attack(
		delayed_attack(
			_event.owner().center(),
			_event.owner().angle(),
			_event.owner().team(),
			_event.owner().environment(),
			*attack_dest_
		)
	);

	context<weapon>().on_castpoint(
		_event.owner()
	);

	this->post_event(
		_event
	);

	return transit<backswing>();
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	events::stop const &
)
{
	return transit<ready>();
}
