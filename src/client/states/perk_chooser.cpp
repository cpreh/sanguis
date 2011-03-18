#include "perk_chooser.hpp"
#include "ingame.hpp"
#include "../events/action.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/tick.hpp"
#include "../gui/perk/chooser.hpp"

sanguis::client::states::perk_chooser::perk_chooser(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	chooser_activation_(
		context<running>().perk_chooser()
	)
{
}

sanguis::client::states::perk_chooser::~perk_chooser()
{
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	events::tick const &
)
{
	context<running>().perk_chooser().process();

	return forward_event();
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	events::action const &_event
)
{
	switch(
		_event.value().type()
	)
	{
	case control::action_type::perk_menu:
	case control::action_type::escape:
		return transit<states::ingame>();
	default:
		return discard_event(); // throw all other input away
	}
}
