#include "unpaused.hpp"
#include "paused.hpp"
#include "../menu_event.hpp"
#include "../../messages/unwrap.hpp"
#include "../../tick_event.hpp"
#include <boost/bind.hpp>

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
	message_event const &m)
{
	return messages::unwrap<
		boost::mpl::vector<
			messages::pause
		>,
		boost::statechart::result
	>(
		*this,
		*m.message(),
		boost::bind(
			&unpaused::handle_default_msg,
			this,
			_1
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
