#include "waiting_for_player.hpp"
#include "../../messages/call/object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <boost/mpl/vector/vector10.hpp>

sanguis::client::states::waiting_for_player::waiting_for_player(
	my_context _ctx
)
:
	my_base(_ctx)
{}

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
		running
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
	events::player_action const &_event
)
{
	return discard_event();
}

boost::statechart::result
sanguis::client::states::waiting_for_player::operator()(
	messages::add_own_player const &_message
)
{
	post_message(
		_message
	);

	return transit<has_player>();
}

boost::statechart::result
sanguis::client::states::waiting_for_player::handle_default_msg(
	messages::base const &
)
{
	return forward_event();	
}
