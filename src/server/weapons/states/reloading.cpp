#include <sanguis/diff_timer.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/reloading.hpp>
#include <sanguis/server/weapons/states/reloading_parameters.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::reloading::reloading(
	my_context _ctx,
	sanguis::server::weapons::states::reloading_parameters const &_parameters
)
:
	my_base(
		_ctx
	),
	reload_time_(
		sanguis::diff_timer::parameters(
			this->context<
				sanguis::server::weapons::weapon
			>().diff_clock(),
			this->context<
				sanguis::server::weapons::weapon
			>().reload_time()->get()
			/
			_parameters.irs().get()
		)
	),
	cancelled_(
		false
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::states::reloading::~reloading()
{
}

boost::statechart::result
sanguis::server::weapons::states::reloading::react(
	sanguis::server::weapons::events::poll const &_event
)
{
	if(
		!reload_time_.expired()
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::weapons::weapon
	>().reset_magazine();

	_event.owner().reloading(
		false,
		this->context<
			sanguis::server::weapons::weapon
		>().type()
	);

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
sanguis::server::weapons::states::reloading::react(
	sanguis::server::weapons::events::stop const &
)
{
	cancelled_ = true;

	return
		this->discard_event();
}
