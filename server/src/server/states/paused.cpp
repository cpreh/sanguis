#include <sanguis/log_parameters.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/info.hpp>
#include <sanguis/messages/client/pause.hpp>
#include <sanguis/messages/client/unpause.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/unpause.hpp>
#include <sanguis/server/dispatch.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::states::log_location()
		/
		FCPPT_TEXT("paused")
	)
);

}

sanguis::server::states::paused::paused()
{
	FCPPT_LOG_DEBUG(
		logger,
		fcppt::log::_
			<< FCPPT_TEXT("create")
	);
}

sanguis::server::states::paused::~paused()
{
	FCPPT_LOG_DEBUG(
		logger,
		fcppt::log::_
			<< FCPPT_TEXT("destroy")
	);
}

boost::statechart::result
sanguis::server::states::paused::react(
	sanguis::server::events::message const &_message
)
{
	auto const handle_default_msg(
		[
			this
		](
			sanguis::server::player_id,
			sanguis::messages::client::base const &
		)
		{
			return
				this->forward_event();
		}
	);

	return
		sanguis::server::dispatch<
			boost::mpl::vector3<
				sanguis::messages::client::info,
				sanguis::messages::client::pause,
				sanguis::messages::client::unpause
			>
		>(
			*this,
			_message,
			handle_default_msg
		);
}

sanguis::messages::call::result
sanguis::server::states::paused::operator()(
	sanguis::server::player_id,
	sanguis::messages::client::info const &
)
{
	this->post_event(
		*this->triggering_event()
	);

	return
		sanguis::messages::call::result(
			this->unpause_impl()
		);
}

sanguis::messages::call::result
sanguis::server::states::paused::operator()(
	sanguis::server::player_id,
	sanguis::messages::client::unpause const &
)
{
	return
		sanguis::messages::call::result(
			this->unpause_impl()
		);
}

sanguis::messages::call::result
sanguis::server::states::paused::operator()(
	sanguis::server::player_id,
	sanguis::messages::client::pause const &
)
{
	FCPPT_LOG_WARNING(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Got superfluous pause")
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

boost::statechart::result
sanguis::server::states::paused::unpause_impl()
{
	this->context<
		sanguis::server::machine
	>().send_to_all(
		sanguis::messages::server::create(
			sanguis::messages::server::unpause()
		)
	);

	return
		this->transit<
			sanguis::server::states::unpaused
		>();
}
