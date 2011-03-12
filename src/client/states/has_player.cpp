#include "has_player.hpp"
//#include "gameover.hpp"
#include "../control/input_translator.hpp"
#include "../control/action_handler.hpp"
#include "../events/action.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../../messages/call/object.hpp"
#include "../../cast_enum.hpp"
#include <sge/console/gfx.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/mpl/vector/vector10.hpp>

sanguis::client::states::has_player::has_player(
	my_context _ctx
)
:
	my_base(_ctx),
	input_translator_(
		fcppt::make_unique_ptr<
			control::input_translator
		>(
			context<machine>().keyboard(),
			context<machine>().mouse(),
			std::tr1::bind(
				&states::has_player::handle_player_action,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	action_handler_(
		fcppt::make_unique_ptr<
			control::action_handler
		>(
			std::tr1::bind(
				&machine::send,
				&context<machine>(),
				std::tr1::placeholders::_1
			),
			std::tr1::ref(
				context<running>().control_environment()
			),
			std::tr1::ref(
				context<machine>().console().gfx().object()
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
	static sanguis::messages::call::object<
		boost::mpl::vector2<
			sanguis::messages::remove_id,
			sanguis::messages::give_weapon
		>,
		has_player
	> dispatcher;

	return
		dispatcher(
			*_event.value(),
			*this,
			std::tr1::bind(
				&has_player::handle_default_msg,
				this,
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::has_player::react(
	events::action const &_event
)
{
	action_handler_->handle_player_action(
		_event.value()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::give_weapon const &_message
)
{
	action_handler_->give_player_weapon(
		SANGUIS_CAST_ENUM(
			weapon_type,
			_message.get<sanguis::messages::roles::weapon>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	messages::remove_id const &
)
{
	return discard_event(); //transit<gameover>();
}

void
sanguis::client::states::has_player::handle_player_action(
	control::player_action const &_action
)
{
	post_event(
		events::action(
			_action
		)
	);
}

boost::statechart::result
sanguis::client::states::has_player::handle_default_msg(
	sanguis::messages::base const &
)
{
	return forward_event();
}
