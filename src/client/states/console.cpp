#include <sanguis/client/states/console.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/control/actions/variant.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/console/object.hpp>
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
	events::overlay const &_event
)
{
	context<running>().console().draw(
		_event.context()
	);

	return this->discard_event();
}
