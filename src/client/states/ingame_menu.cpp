#include "ingame_menu.hpp"
#include "../events/action.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/tick.hpp"

sanguis::client::states::ingame_menu::ingame_menu(
	my_context _ctx
)
:
	my_base(
		_ctx
	)
{
}

sanguis::client::states::ingame_menu::~ingame_menu()
{
}
