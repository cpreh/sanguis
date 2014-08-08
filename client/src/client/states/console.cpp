#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/console/object.hpp>
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
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/running.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::console::console(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	pause_(
		sanguis::client::make_send_callback(
			this->context<
				sanguis::client::machine
			>()
		)
	),
	console_activation_(
		this->context<
			sanguis::client::states::running
		>().console()
	)
{
}

sanguis::client::states::console::~console()
{
}

boost::statechart::result
sanguis::client::states::console::react(
	sanguis::client::events::action const &_event
)
{
	sanguis::client::control::actions::variant const action(
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
					sanguis::client::states::ingame
				>();
		default:
			break;
		}
	}

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::console::react(
	sanguis::client::events::overlay const &_event
)
{
	this->context<
		sanguis::client::states::running
	>().console().draw(
		_event.context()
	);

	return
		this->forward_event();
}
