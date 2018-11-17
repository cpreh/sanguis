#include <sanguis/log_parameters.hpp>
#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/dispatch_default_function.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/server/add_own_player.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::waiting_for_player::waiting_for_player(
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
				FCPPT_TEXT("waiting_for_player")
			}
		)
	}
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
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
			brigand::list<
				sanguis::messages::server::add_own_player
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
sanguis::client::states::waiting_for_player::react(
	sanguis::client::events::action const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::to_optional<
			sanguis::client::control::actions::nullary
		>(
			_event.value().get()
		),
		[
			this
		](
			sanguis::client::control::actions::nullary const &_nullary
		)
		{
			switch(
				_nullary.type()
			)
			{
			case sanguis::client::control::actions::nullary_type::escape:
				context<
					sanguis::client::machine
				>().quit();

				return;
			case sanguis::client::control::actions::nullary_type::console:
			case sanguis::client::control::actions::nullary_type::change_world:
			case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
			case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
			case sanguis::client::control::actions::nullary_type::perk_menu:
			case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
			case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
				return;
			}

			FCPPT_ASSERT_UNREACHABLE;
		}
	);

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
