#include "perk_chooser.hpp"
#include "ingame.hpp"
#include "../make_send_callback.hpp"
#include "../events/action.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/overlay.hpp"
#include "../events/render.hpp"
#include "../events/tick.hpp"
#include "../gui/perk/chooser.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

sanguis::client::states::perk_chooser::perk_chooser(
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
		case control::actions::nullary_type::perk_menu:
			return transit<states::ingame>();
		default:
			break;
		}
	}

	return this->forward_event();
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	events::overlay const &
)
{
	perk_chooser_gui_.draw();

	return this->discard_event();
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	events::tick const &_event
)
{
	perk_chooser_gui_.process(
		_event.delta()
	);

	return this->discard_event();
}
