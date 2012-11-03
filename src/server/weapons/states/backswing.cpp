#include <sanguis/diff_timer.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/events/reset.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/reloading.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::backswing::backswing(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	cooldown_(
		sanguis::diff_timer::parameters(
			this->context<
				sanguis::server::weapons::weapon
			>().diff_clock(),
			this->context<
				sanguis::server::weapons::weapon
			>().backswing_time().get()
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::states::backswing::~backswing()
{
}

boost::statechart::result
sanguis::server::weapons::states::backswing::react(
	sanguis::server::weapons::events::poll const &_event
)
{
	if(
		!cooldown_.expired()
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::weapons::weapon
	>().use_magazine_item();

	_event.owner().attack_ready();

	this->post_event(
		_event
	);

	if(
		this->context<
			sanguis::server::weapons::weapon
		>().magazine_empty()
	)
	{
		_event.owner().start_reloading();

		this->context<
			sanguis::server::weapons::weapon
		>().magazine_exhausted();

		return
			this->transit<
				sanguis::server::weapons::states::reloading
			>();
	}

	return
		this->transit<
			sanguis::server::weapons::states::ready
		>();
}
