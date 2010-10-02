#include "ingame.hpp"
#include "ingame_menu.hpp"
#include "perk_chooser.hpp"
#include "../events/menu.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

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
	events::menu const &_event
)
{
	switch(
		_event.type()
	)
	{
	case control::menu_action::perk:
		return transit<states::perk_chooser>();
	case control::menu_action::options:
		return transit<states::ingame_menu>();
	}

	throw exception(
		FCPPT_TEXT("Invalid menu event!")
	);
}
