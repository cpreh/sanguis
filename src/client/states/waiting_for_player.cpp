#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/create.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::client::states::waiting_for_player::waiting_for_player(
	my_context _ctx
)
:
	my_base(_ctx)
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering waiting_for_player")
	);
}

sanguis::client::states::waiting_for_player::~waiting_for_player()
{
}

boost::statechart::result
sanguis::client::states::waiting_for_player::react(
	events::message const &_event
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector1<
			sanguis::messages::add_own_player
		>,
		waiting_for_player
	> dispatcher;

	return
		dispatcher(
			*_event.value(),
			*this,
			std::tr1::bind(
				&waiting_for_player::handle_default_msg,
				this,
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::waiting_for_player::react(
	events::action const &_event
)
{
	return discard_event();
}

sanguis::client::states::waiting_for_player::result_type
sanguis::client::states::waiting_for_player::operator()(
	messages::add_own_player const &_message
)
{
	post_event(
		events::message(
			messages::create(
				_message
			)
		)
	);

	return transit<has_player>();
}

boost::statechart::result
sanguis::client::states::waiting_for_player::handle_default_msg(
	sanguis::messages::base const &
)
{
	return forward_event();
}
