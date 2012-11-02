#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/message_functor.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/unpause.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/log_parameters.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
	events::message const &_message
)
{
	if(
		!context<
			sanguis::server::states::running
		>().global_context().has_player(
			_message.id()
		)
	)
		return this->forward_event();

	typedef message_functor<
		paused,
		boost::statechart::result
	> functor_type;

	functor_type functor(
		*this,
		_message.id()
	);

	static messages::call::object<
		boost::mpl::vector2<
			messages::player_pause,
			messages::player_unpause
		>,
		functor_type
	>::type dispatcher;

	return
		dispatcher(
			*_message.get(),
			functor,
			std::tr1::bind(
				&paused::handle_default_msg,
				this,
				_message.id(),
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	server::player_id,
	messages::player_unpause const &
)
{
	context<machine>().send_to_all(
		*messages::create(
			messages::unpause()
		)
	);

	return transit<unpaused>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	server::player_id,
	messages::player_pause const &
)
{
	FCPPT_LOG_WARNING(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("got superfluous pause")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	server::player_id,
	messages::base const &
)
{
	return forward_event();
}
