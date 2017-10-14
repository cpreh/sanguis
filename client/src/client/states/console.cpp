#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/console.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/running.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::console::console(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	pause_(
		sanguis::client::make_send_callback(
			this->context<
				sanguis::client::machine
			>()
		)
	)
{
}

sanguis::client::states::console::~console()
{
}

boost::statechart::result
sanguis::client::states::console::react(
	sanguis::client::events::action const &_event
)
{
	return
		fcppt::optional::maybe(
			fcppt::variant::to_optional<
				sanguis::client::control::actions::nullary
			>(
				_event.value().get()
			),
			[
				this
			]{
				return
					this->discard_event();
			},
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
				case sanguis::client::control::actions::nullary_type::console:
					return
						this->transit<
							sanguis::client::states::ingame
						>();
				case sanguis::client::control::actions::nullary_type::change_world:
				case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
				case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
				case sanguis::client::control::actions::nullary_type::escape:
				case sanguis::client::control::actions::nullary_type::perk_menu:
				case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
				case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
					return
						this->discard_event();
				}

				FCPPT_ASSERT_UNREACHABLE;
			}
		);
}

boost::statechart::result
sanguis::client::states::console::react(
	sanguis::client::events::overlay const &_event
)
{
	this->context<
		sanguis::client::states::running
	>().console().draw(
		_event.context()
	);

	return
		this->forward_event();
}

boost::statechart::result
sanguis::client::states::console::react(
	sanguis::client::events::input const &_event
)
{
	this->context<
		sanguis::client::states::running
	>().console().input_event(
		_event.get()
	);

	return
		this->forward_event();
}
