#include "paused.hpp"
#include "unpaused.hpp"
#include "../events/disconnect.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../message_functor.hpp"
#include "../log.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>

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
	> dispatcher;
	
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
	net::id,
	messages::player_unpause const &
)
{
	context<machine>().send_to_all(
		messages::create(
			messages::unpause()
		)
	);

	return transit<unpaused>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id,
	messages::player_pause const &
)
{
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("got superfluous pause")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	net::id,
	messages::base const &
)
{
	return forward_event();
}

fcppt::log::object &
sanguis::server::states::paused::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("paused")
		)
	);

	return my_logger;
}
