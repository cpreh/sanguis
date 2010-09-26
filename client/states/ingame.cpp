#include "ingame.hpp"
#include "ingame_menu.hpp"
#include "../events/menu.hpp"

sanguis::client::states::ingame::ingame(
	my_context _ctx
)
:
	my_base(
		_ctx
	)
{
}

boost::statechart::result
sanguis::client::states::ingame::react(
	events::menu const &
)
{
	return transit<states::ingame_menu>();
}
