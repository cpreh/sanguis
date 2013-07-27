#include <sanguis/diff_timer.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::castpoint::castpoint(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	attack_time_(
		sanguis::diff_timer::parameters(
			this->context<
				sanguis::server::weapons::weapon
			>().diff_clock(),
			this->context<
				sanguis::server::weapons::weapon
			>().cast_point().get()
		)
	),
	attack_dest_()
{
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::states::castpoint::~castpoint()
{
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::shoot const &_event
)
{
	// TODO: use constructor instead!
	attack_dest_ = _event.to();

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::poll const &_event
)
{
	if(
		!attack_time_.expired()
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::weapons::weapon
	>().do_attack(
		sanguis::server::weapons::delayed_attack(
			_event.owner().center(),
			_event.owner().angle(),
			_event.owner().team(),
			_event.owner().environment(),
			*attack_dest_
		)
	);

	this->post_event(
		_event
	);

	return
		this->transit<
			sanguis::server::weapons::states::backswing
		>();
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	sanguis::server::weapons::events::stop const &
)
{
	return
		this->transit<
			sanguis::server::weapons::states::ready
		>();
}
