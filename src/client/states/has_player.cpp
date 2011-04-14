#include "has_player.hpp"
#include "../control/action_handler.hpp"
#include "../control/input_translator.hpp"
#include "../console/object.hpp"
#include "../events/action.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/tick.hpp"
#include "../log.hpp"
#include "../perk/cast.hpp"
#include "../perk/state.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/create.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../cast_enum.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
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
			fcppt::ref(
				context<machine>().cursor()
			),
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
			fcppt::ref(
				context<running>().control_environment()
			),
			fcppt::ref(
				context<running>().console().sge_console()
			)
		)
	),
	perk_state_(
		fcppt::make_unique_ptr<
			perk::state
		>(
			std::tr1::bind(
				&states::has_player::send_perk_choose,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering has_player")
	);
}

sanguis::client::states::has_player::~has_player()
{
}

boost::statechart::result
sanguis::client::states::has_player::react(
	events::message const &_event
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector4<
			sanguis::messages::available_perks,
			sanguis::messages::level_up,
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
	action_handler_->handle_action(
		_event.value()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::available_perks const &_message
)
{
	perk_state_->perks(
		client::perk::cast(
			_message.get<sanguis::messages::perk_list>()
		)
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
	messages::level_up const &_message
)
{
	perk_state_->level(
		client::level(
			_message.get<sanguis::messages::level_type>()
		)
	);

	return forward_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	messages::remove_id const &
)
{
	return discard_event(); //transit<gameover>();
}

sanguis::client::perk::state &
sanguis::client::states::has_player::perk_state()
{
	return *perk_state_;
}

void
sanguis::client::states::has_player::handle_player_action(
	control::actions::any const &_action
)
{
	this->post_event(
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

void
sanguis::client::states::has_player::send_perk_choose(
	sanguis::perk_type::type const _type
)
{
	context<machine>().send(
		messages::create(
			messages::player_choose_perk(
				_type
			)
		)
	);
}
