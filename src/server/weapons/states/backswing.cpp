#include <sanguis/diff_timer.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/backswing_parameters.hpp>
#include <sanguis/server/weapons/states/reloading.hpp>
#include <sanguis/server/weapons/states/reloading_parameters.hpp>
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
	my_context _ctx,
	sanguis::server::weapons::states::backswing_parameters const &_parameters
)
:
	my_base(
		_ctx
	),
	cancelled_(
		false
	),
	cooldown_(
		sanguis::diff_timer::parameters(
			this->context<
				sanguis::server::weapons::weapon
			>().diff_clock(),
			this->context<
				sanguis::server::weapons::weapon
			>().backswing_time().get()
			/
			_parameters.ias().get()
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

	_event.owner().attacking(
		false,
		this->context<
			sanguis::server::weapons::weapon
		>().type()
	);

	if(
		this->context<
			sanguis::server::weapons::weapon
		>().magazine_empty()
	)
	{
		this->context<
			sanguis::server::weapons::weapon
		>().magazine_exhausted();

		if(
			cancelled_
		)
			this->post_event(
				sanguis::server::weapons::events::stop()
			);

		_event.owner().reloading(
			true,
			this->context<
				sanguis::server::weapons::weapon
			>().type()
		);

		return
			this->transit<
				sanguis::server::weapons::states::reloading
			>(
				sanguis::server::weapons::states::reloading_parameters(
					_event.owner().irs()
				)
			);
	}

	if(
		!cancelled_
	)
		this->post_event(
			sanguis::server::weapons::events::shoot(
				_event.owner()
			)
		);

	return
		this->transit<
			sanguis::server::weapons::states::ready
		>();
}

boost::statechart::result
sanguis::server::weapons::states::backswing::react(
	sanguis::server::weapons::events::stop const &
)
{
	cancelled_ = true;

	return
		this->discard_event();
}
