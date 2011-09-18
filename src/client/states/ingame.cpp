#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/console.hpp>
#include <sanguis/client/states/ingame_menu.hpp>
#include <sanguis/client/states/perk_chooser.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/control/actions/variant.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

sanguis::client::states::ingame::ingame(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	scoped_cursor_(
		context<machine>().cursor()
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
	control::actions::variant const action(
		_event.value().get()
	);

	if(
		fcppt::variant::holds_type<
			control::actions::nullary
		>(
			action
		)
	)
	{
		switch(
			action.get<
				control::actions::nullary
			>().type()
		)
		{
		case control::actions::nullary_type::console:
			return transit<states::console>();
		case control::actions::nullary_type::perk_menu:
			return transit<states::perk_chooser>();
		case control::actions::nullary_type::escape:
			context<machine>().quit();

			return this->discard_event();
			//return transit<states::ingame_menu>();
		default:
			break;
		}
	}

	return this->forward_event();
}
