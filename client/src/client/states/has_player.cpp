#include <sanguis/log_parameters.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/dispatch_default_function.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/control/action_handler.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/perk/make_tree.hpp>
#include <sanguis/client/perk/remaining_levels.hpp>
#include <sanguis/client/perk/send_callback.hpp>
#include <sanguis/client/perk/state.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/client/choose_perk.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/roles/level.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/roles/perk_tree.hpp>
#include <sanguis/messages/roles/perk_type.hpp>
#include <sanguis/messages/roles/remaining_perk_levels.hpp>
#include <sanguis/messages/server/available_perks.hpp>
#include <sanguis/messages/server/level_up.hpp>
#include <sanguis/messages/server/remove_id.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
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
	log_{
		this->context<
			sanguis::client::machine
		>().log_context(),
		sanguis::client::states::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("has_player")
			}
		)
	},
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
			sanguis::client::perk::send_callback{
				std::bind(
					&sanguis::client::states::has_player::send_perk_choose,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
	FCPPT_LOG_DEBUG(
		log_,
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
			boost::mpl::vector3<
				sanguis::messages::server::available_perks,
				sanguis::messages::server::level_up,
				sanguis::messages::server::remove_id
			>
		>(
			*this,
			_event,
			sanguis::client::dispatch_default_function{
				handle_default_msg
			}
		);
}

boost::statechart::result
sanguis::client::states::has_player::react(
	sanguis::client::events::tick const &_event
)
{
	this->context<
		sanguis::client::states::running
	>().update(
		_event,
		action_handler_->cursor_position()
	);

	return
		this->discard_event();
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

sanguis::messages::call::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::server::available_perks const &_message
)
{
	perk_state_->perks(
		sanguis::client::perk::make_tree(
			_message.get<
				sanguis::messages::roles::perk_tree
			>()
		),
		sanguis::client::perk::remaining_levels(
			sanguis::client::level(
				_message.get<
					sanguis::messages::roles::remaining_perk_levels
				>()
			)
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::server::level_up const &_message
)
{
	perk_state_->player_level(
		sanguis::client::player_level(
			sanguis::client::level(
				_message.get<
					sanguis::messages::roles::level
				>()
			)
		)
	);

	return
		sanguis::messages::call::result(
			this->forward_event()
		);
}

sanguis::messages::call::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::server::remove_id const &
)
{
	return
		sanguis::messages::call::result(
			this->discard_event()
		); //transit<gameover>();
}

sanguis::client::perk::state &
sanguis::client::states::has_player::perk_state()
{
	return
		*perk_state_;
}

void
sanguis::client::states::has_player::send_perk_choose(
	sanguis::perk_type const _type
)
{
	this->context<
		sanguis::client::machine
	>().send(
		sanguis::messages::client::create(
			sanguis::messages::client::choose_perk(
				sanguis::messages::roles::perk_type{} =
					_type
			)
		)
	);
}
