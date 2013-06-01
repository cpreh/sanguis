#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/control/actions/variant.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/console.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/ingame_menu.hpp>
#include <sanguis/client/states/perk_chooser.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::ingame::ingame(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	scoped_cursor_(
		this->context<
			sanguis::client::machine
		>().cursor()
	)
{
}

sanguis::client::states::ingame::~ingame()
{
}

boost::statechart::result
sanguis::client::states::ingame::react(
	sanguis::client::events::action const &_event
)
{
	control::actions::variant const action(
		_event.value().get()
	);

	if(
		fcppt::variant::holds_type<
			sanguis::client::control::actions::nullary
		>(
			action
		)
	)
	{
		switch(
			action.get<
				sanguis::client::control::actions::nullary
			>().type()
		)
		{
		case sanguis::client::control::actions::nullary_type::console:
			return
				this->transit<
					sanguis::client::states::console
				>();
		case sanguis::client::control::actions::nullary_type::perk_menu:
			return
				this->transit<
					sanguis::client::states::perk_chooser
				>();
		case sanguis::client::control::actions::nullary_type::escape:
			this->context<
				sanguis::client::machine
			>().quit();

			return
				this->discard_event();
			//return transit<states::ingame_menu>();
		default:
			break;
		}
	}

	return
		this->forward_event();
}
