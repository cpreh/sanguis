#include "console.hpp"
#include "has_player.hpp"
#include "ingame.hpp"
#include "../make_send_callback.hpp"
#include "../control/actions/nullary.hpp"
#include "../control/actions/nullary_type.hpp"
#include "../control/actions/variant.hpp"
#include "../events/action.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/overlay.hpp"
#include "../events/render.hpp"
#include "../events/tick.hpp"
#include "../console/object.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

sanguis::client::states::console::console(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	pause_(
		client::make_send_callback(
			context<machine>()
		)
	),
	console_activation_(
		context<states::running>().console()
	)
{
}

sanguis::client::states::console::~console()
{
}

boost::statechart::result
sanguis::client::states::console::react(
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
			return transit<states::ingame>();
		default:
			break;
		}
	}

	return this->discard_event();
}

boost::statechart::result
sanguis::client::states::console::react(
	events::overlay const &
)
{
	context<running>().console().draw();

	return this->discard_event();
}
