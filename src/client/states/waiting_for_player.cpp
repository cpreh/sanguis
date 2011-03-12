#include "waiting_for_player.hpp"
#include "has_player.hpp"
#include "ingame.hpp"
#include "../events/action.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/create.hpp"
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
