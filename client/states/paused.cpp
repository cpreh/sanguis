#include "paused.hpp"
#include "unpaused.hpp"
#include "../../dispatch_type.hpp"
#include "../../messages/unpause.hpp"
#include <boost/bind.hpp>

sanguis::client::states::paused::paused(my_context ctx)
	: my_base(ctx)
{
	context<running>().pause(true);
}

boost::statechart::result
sanguis::client::states::paused::react(
	tick_event const &t)
{
	context<running>().process(t.delta());
	context<running>().draw(t.delta());
	return discard_event();
}

boost::statechart::result
sanguis::client::states::paused::react(
	message_event const &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::unpause
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&paused::handle_default_msg, this, _1));
}

boost::statechart::result sanguis::client::states::paused::operator()(
	messages::unpause const &)
{
	return transit<unpaused>();
}

boost::statechart::result sanguis::client::states::paused::handle_default_msg(
	messages::base const &)
{
	return forward_event();
}
