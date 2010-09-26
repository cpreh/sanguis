#include "perk_chooser.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/call/object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <boost/mpl/vector/vector10.hpp>

sanguis::client::states::perk_chooser::perk_chooser(
	my_context ctx
)
:
	my_base(ctx),
	chooser_activation_(
		context<running>().perk_chooser()
	)
{
	context<
		running
	>().pause(
		true
	);
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
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
sanguis::client::states::perk_chooser::react(
	events::message const &_event
)
{
	static messages::call::object<
		boost::mpl::vector1<
			messages::unpause
		>,
		perk_chooser	
	> dispatcher;

	return dispatcher(
		*_event.value(),
		*this,
		std::tr1::bind(
			&perk_chooser::handle_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::client::states::perk_chooser::operator()(
	messages::unpause const &
)
{
	//return transit<states::perk_chooser>();
}

boost::statechart::result
sanguis::client::states::perk_chooser::handle_default_msg(
	messages::base const &
)
{
	return forward_event();
}
