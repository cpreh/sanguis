#include "paused.hpp"
#include "unpaused.hpp"
#include "../menu_event.hpp"
#include "../../tick_event.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/call/object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <boost/mpl/vector/vector10.hpp>

sanguis::client::states::paused::paused(my_context ctx)
:
	my_base(ctx),
	chooser_activation_(
		context<running>().perk_chooser())
{
	context<running>().pause(true);
}

boost::statechart::result
sanguis::client::states::paused::react(
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
sanguis::client::states::paused::react(
	message_event const &m)
{
	static messages::call::object<
		boost::mpl::vector1<
			messages::unpause
		>,
		paused
	> dispatcher;

	return dispatcher(
		*m.message(),
		*this,
		std::tr1::bind(
			&paused::handle_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::client::states::paused::operator()(
	messages::unpause const &
)
{
	return transit<unpaused>();
}

boost::statechart::result
sanguis::client::states::paused::handle_default_msg(
	messages::base const &
)
{
	return forward_event();
}
