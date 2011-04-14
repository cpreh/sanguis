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
	perk_chooser_gui_(
		context<machine>().gui(),
		context<has_player>().perk_state()
	)
{
}

sanguis::client::states::perk_chooser::~perk_chooser()
{
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	events::action const &_event
)
{
	return discard_event(); // FIXME
#if 0
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
#endif
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	events::tick const &_event
)
{
	perk_chooser_gui_.process(
		_event.delta()
	);

	return forward_event();
}
