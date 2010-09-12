#include "unpaused.hpp"
#include "paused.hpp"
#include "../events/message.hpp"
#include "../events/menu.hpp"
#include "../events/tick.hpp"
#include "../../messages/call/object.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::states::unpaused::unpaused(
	my_context ctx
)
:
	my_base(ctx)
{
	context<running>().pause(false);
}

boost::statechart::result
sanguis::client::states::unpaused::react(
	events::tick const &_event
)
{
	context<running>().process(
		_event
	);

	context<running>().draw(
		_event
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::unpaused::react(
	events::message const &_event
)
{
	static messages::call::object<
		boost::mpl::vector1<
			messages::pause
		>,
		unpaused
	> dispatcher;

	return dispatcher(
		*_event.value(),
		*this,
		std::tr1::bind(
			&unpaused::handle_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}
boost::statechart::result
sanguis::client::states::unpaused::react(
	events::menu const &_event
)
{
	context<machine>().quit(); // TODO!
	return discard_event(); // TODO!
}

boost::statechart::result
sanguis::client::states::unpaused::operator()(
	messages::pause const &
)
{
	return transit<paused>();
}

boost::statechart::result
sanguis::client::states::unpaused::handle_default_msg(
	messages::base const &
)
{
	return forward_event();
}
