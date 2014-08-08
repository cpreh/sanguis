#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/ingame_menu.hpp>


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
