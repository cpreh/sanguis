#include <sanguis/log_parameters.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/message_functor.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/player_pause.hpp>
#include <sanguis/messages/player_unpause.hpp>
#include <sanguis/messages/unpause.hpp>
#include <sanguis/messages/call/object.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <ostream>
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
}

sanguis::server::states::paused::~paused()
{
}

boost::statechart::result
sanguis::server::states::paused::react(
	sanguis::server::events::message const &_message
)
{
	if(
		!this->context<
			sanguis::server::states::running
		>().global_context().has_player(
			_message.id()
		)
	)
		return this->forward_event();

	typedef sanguis::server::message_functor<
		sanguis::server::states::paused,
		boost::statechart::result
	> functor_type;

	functor_type functor(
		*this,
		_message.id()
	);

	static sanguis::messages::call::object<
		boost::mpl::vector2<
			sanguis::messages::player_pause,
			sanguis::messages::player_unpause
		>,
		functor_type
	> dispatcher;

	return
		dispatcher(
			*_message.get(),
			functor,
			std::bind(
				&sanguis::server::states::paused::handle_default_msg,
				this,
				_message.id(),
				std::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	sanguis::server::player_id,
	sanguis::messages::player_unpause const &
)
{
	this->context<
		sanguis::server::machine
	>().send_to_all(
		*sanguis::messages::create(
			sanguis::messages::unpause()
		)
	);

	return
		this->transit<
			sanguis::server::states::unpaused
		>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	sanguis::server::player_id,
	sanguis::messages::player_pause const &
)
{
	FCPPT_LOG_WARNING(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("got superfluous pause")
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	sanguis::server::player_id,
	sanguis::messages::base const &
)
{
	return
		this->forward_event();
}
