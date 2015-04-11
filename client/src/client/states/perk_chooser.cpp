#include <sanguis/client/cursor.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/perk_chooser.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::perk_chooser::perk_chooser(
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
	),
	perk_chooser_gui_(
		this->context<
			sanguis::client::states::has_player
		>().perk_state(),
		this->context<
			sanguis::client::machine
		>().gui_style(),
		this->context<
			sanguis::client::machine
		>().renderer(),
		this->context<
			sanguis::client::machine
		>().viewport_manager(),
		this->context<
			sanguis::client::machine
		>().font_object(),
		this->context<
			sanguis::client::machine
		>().cursor(),
		this->context<
			sanguis::client::machine
		>().keyboard()
	),
	hud_details_(
		this->context<
			sanguis::client::states::running
		>().hud_gui()
	)
{
}

sanguis::client::states::perk_chooser::~perk_chooser()
{
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	sanguis::client::events::action const &_event
)
{
	return
		fcppt::maybe(
			fcppt::variant::to_optional<
				sanguis::client::control::actions::nullary
			>(
				_event.value().get()
			),
			[
				this
			]{
				return
					this->forward_event();
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
				case sanguis::client::control::actions::nullary_type::perk_menu:
					return
						this->transit<
							sanguis::client::states::ingame
						>();
				case sanguis::client::control::actions::nullary_type::change_world:
				case sanguis::client::control::actions::nullary_type::console:
				case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
				case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
				case sanguis::client::control::actions::nullary_type::escape:
				case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
				case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
					return
						this->forward_event();
				}

				FCPPT_ASSERT_UNREACHABLE;
			}
		);
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	sanguis::client::events::overlay const &_event
)
{
	perk_chooser_gui_.draw(
		_event.context()
	);

	this->context<
		sanguis::client::machine
	>().cursor_gfx().draw(
		_event.context()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(
	sanguis::client::events::tick const &_event
)
{
	perk_chooser_gui_.process(
		_event.delta()
	);

	return
		this->forward_event();
}
