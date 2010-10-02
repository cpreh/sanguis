#include "has_player.hpp"
#include "../control/input_handler.hpp"
#include "../events/player_action.hpp"
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::states::has_player::has_player(
	my_context _ctx
)
:
	my_base(_ctx),
	input_translator_(
		fcppt::make_unique_ptr<
			control::input_handler
		>(
			context<machine>().input_system(),
			std::tr1::bind(
				&states::has_player::handle_player_action,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{}

sanguis::client::states::has_player::~has_player()
{
}

boost::statechart::result
sanguis::client::states::has_player::react(
	events::message const &_event
)
{
}

boost::statechart::result
sanguis::client::states::has_player::react(
	events::player_action const &_event
)
{
	action_handler_.handle_player_action(
		_event.action()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	messages::remove_id const &_message
)
{
	return transit<gameover>();
}

void
sanguis::client::states::has_player::handle_player_action(
	control::player_action const &_action
)
{
	post_event(
		events::player_action(
			_action
		)
	);
}
