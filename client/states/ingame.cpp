#include "ingame.hpp"
#include "ingame_menu.hpp"
#include "perk_chooser.hpp"
#include "../events/action.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"

sanguis::client::states::ingame::ingame(
	my_context _ctx
)
:
	my_base(
		_ctx
	)
{
}

sanguis::client::states::ingame::~ingame()
{
}

boost::statechart::result
sanguis::client::states::ingame::react(
	events::action const &_event
)
{
	switch(
		_event.value().type()
	)
	{
	case control::action_type::perk_menu:
		return transit<states::perk_chooser>();
	case control::action_type::escape:
		return transit<states::ingame_menu>();
	default:
		// forward the event to the inner state, so it can be processed normally
		return forward_event();
	}
}
