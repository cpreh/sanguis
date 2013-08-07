#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/control/action_handler.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/perk/make_tree.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/messages/available_perks.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/give_weapon.hpp>
#include <sanguis/messages/level_up.hpp>
#include <sanguis/messages/player_choose_perk.hpp>
#include <sanguis/messages/remove_id.hpp>
#include <sanguis/messages/call/object.hpp>
#include <alda/serialization/load/optional.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::has_player::has_player(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	action_handler_(
		fcppt::make_unique_ptr<
			sanguis::client::control::action_handler
		>(
			sanguis::client::make_send_callback(
				this->context<
					sanguis::client::machine
				>()
			),
			this->context<
				sanguis::client::states::running
			>().control_environment(),
			this->context<
				sanguis::client::states::running
			>().console().sge_console()
		)
	),
	perk_state_(
		fcppt::make_unique_ptr<
			sanguis::client::perk::state
		>(
			std::bind(
				&sanguis::client::states::has_player::send_perk_choose,
				this,
				std::placeholders::_1
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering has_player")
	);
}

sanguis::client::states::has_player::~has_player()
{
}

boost::statechart::result
sanguis::client::states::has_player::react(
	sanguis::client::events::message const &_event
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
			std::bind(
				&sanguis::client::states::has_player::handle_default_msg,
				this,
				std::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::has_player::react(
	sanguis::client::events::action const &_event
)
{
	action_handler_->handle_action(
		_event.value()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::available_perks const &_message
)
{
	perk_state_->perks(
		sanguis::client::perk::make_tree(
			_message.get<
				sanguis::messages::perk_tree
			>()
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::give_weapon const &_message
)
{
	action_handler_->give_player_weapon(
		_message.get<
			sanguis::messages::roles::weapon
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::level_up const &_message
)
{
	perk_state_->player_level(
		sanguis::client::player_level(
			sanguis::client::level(
				_message.get<
					sanguis::messages::level
				>()
			)
		)
	);

	return
		this->forward_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::remove_id const &
)
{
	return
		this->discard_event(); //transit<gameover>();
}

sanguis::client::perk::state &
sanguis::client::states::has_player::perk_state()
{
	return
		*perk_state_;
}

boost::statechart::result
sanguis::client::states::has_player::handle_default_msg(
	sanguis::messages::base const &
)
{
	return
		this->forward_event();
}

void
sanguis::client::states::has_player::send_perk_choose(
	sanguis::perk_type const _type
)
{
	this->context<
		sanguis::client::machine
	>().send(
		*sanguis::messages::create(
			sanguis::messages::player_choose_perk(
				_type
			)
		)
	);
}
