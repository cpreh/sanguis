#include <sanguis/weapon_status.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/log.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/reload.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/idle.hpp>
#include <sanguis/server/weapons/states/reloading.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::weapons::states::idle::idle(
	my_context _ctx
)
:
	my_base(
		_ctx
	)
{
	this->context<
		sanguis::server::weapons::weapon
	>().weapon_status(
		sanguis::weapon_status::nothing
	);

	FCPPT_LOG_VERBOSE(
		sanguis::server::weapons::log(),
		fcppt::log::_
			<< FCPPT_TEXT("idle: ")
			<< this
	);
}

sanguis::server::weapons::states::idle::~idle()
{
}

boost::statechart::result
sanguis::server::weapons::states::idle::react(
	sanguis::server::weapons::events::shoot const &
)
{
	if(
		this->context<
			sanguis::server::weapons::weapon
		>().magazine_empty()
	)
	{
		this->post_event(
			sanguis::server::weapons::events::reload()
		);

		return
			this->discard_event();
	}

	return
		this->context<
			sanguis::server::weapons::weapon
		>().owner_target_in_range()
		?
			this->transit<
				sanguis::server::weapons::states::castpoint
			>()
		:
			this->discard_event()
		;
}

boost::statechart::result
sanguis::server::weapons::states::idle::react(
	sanguis::server::weapons::events::reload const &
)
{
	return
		this->context<
			sanguis::server::weapons::weapon
		>().reload_time().has_value()
		?
			this->transit<
				sanguis::server::weapons::states::reloading
			>()
		:
			this->discard_event()
		;
}

boost::statechart::result
sanguis::server::weapons::states::idle::react(
	sanguis::server::weapons::events::poll const &
)
{
	if(
		this->context<
			sanguis::server::weapons::weapon
		>().magazine_empty()
	)
		this->post_event(
			sanguis::server::weapons::events::reload()
		);

	return
		this->discard_event();
}
