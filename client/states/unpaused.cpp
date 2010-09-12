#include "unpaused.hpp"
#include "paused.hpp"
#include "../menu_event.hpp"
#include "../events/message.hpp"
#include "../../messages/call/object.hpp"
#include "../../tick_event.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::states::unpaused::unpaused(
	my_context ctx)
:
	my_base(ctx)
{
	context<running>().pause(false);
}

boost::statechart::result
sanguis::client::states::unpaused::react(
	tick_event const &t)
{
	context<running>().process(
		tick_event(
			t.delta()
		)
	);

	context<running>().draw(
		tick_event(
			t.delta()
		)
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
sanguis::client::states::unpaused::operator()(
	messages::pause const &)
{
	return transit<paused>();
}

boost::statechart::result
sanguis::client::states::unpaused::handle_default_msg(
	messages::base const &)
{
	return forward_event();
}
