#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/control/actions/variant.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/server/add_own_player.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::waiting_for_player::waiting_for_player(
	my_context _ctx
)
:
	my_base(
		_ctx
	)
{
	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering waiting_for_player")
	);
}

sanguis::client::states::waiting_for_player::~waiting_for_player()
{
}

boost::statechart::result
sanguis::client::states::waiting_for_player::react(
	sanguis::client::events::message const &_event
)
{
	auto const handle_default_msg(
		[
			this
		](
			sanguis::messages::server::base const &
		)
		{
			return
				this->forward_event();
		}
	);

	return
		sanguis::client::dispatch<
			boost::mpl::vector1<
				sanguis::messages::server::add_own_player
			>
		>(
			*this,
			_event,
			handle_default_msg
		);
}

boost::statechart::result
sanguis::client::states::waiting_for_player::react(
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
		&&
		action.get<
			sanguis::client::control::actions::nullary
		>().type()
		==
		sanguis::client::control::actions::nullary_type::escape
	)
		context<
			sanguis::client::machine
		>().quit();

	return
		this->discard_event();
}

sanguis::messages::call::result
sanguis::client::states::waiting_for_player::operator()(
	sanguis::messages::server::add_own_player const &
)
{
	this->post_event(
		*this->triggering_event()
	);

	return
		sanguis::messages::call::result(
			this->transit<
				sanguis::client::states::has_player
			>()
		);
}
