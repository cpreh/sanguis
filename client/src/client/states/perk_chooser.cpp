#include <sanguis/client/cursor.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/perk_chooser.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::states::perk_chooser::perk_chooser(my_context _ctx)
    : my_base(std::move(_ctx)),
      pause_(sanguis::client::make_send_callback(
          fcppt::make_ref(this->context<sanguis::client::machine>()))),
      perk_chooser_gui_(
          fcppt::make_ref(this->context<sanguis::client::states::has_player>().perk_state()),
          fcppt::make_cref(this->context<sanguis::client::machine>().gui_style()),
          fcppt::make_ref(this->context<sanguis::client::machine>().renderer()),
          fcppt::make_ref(this->context<sanguis::client::machine>().viewport_manager()),
          fcppt::make_ref(this->context<sanguis::client::machine>().font_object())),
      hud_details_(fcppt::make_ref(this->context<sanguis::client::states::running>().hud_gui()))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::states::perk_chooser::~perk_chooser() = default;

boost::statechart::result
sanguis::client::states::perk_chooser::react(sanguis::client::events::action const &_event)
{
  return fcppt::optional::maybe(
      fcppt::variant::to_optional<sanguis::client::control::actions::nullary>(_event.value().get()),
      [this] { return this->forward_event(); },
      [this](sanguis::client::control::actions::nullary const &_nullary)
      {
        switch (_nullary.type())
        {
        case sanguis::client::control::actions::nullary_type::perk_menu:
          return this->transit<sanguis::client::states::ingame>();
        case sanguis::client::control::actions::nullary_type::change_world:
        case sanguis::client::control::actions::nullary_type::console:
        case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
        case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
        case sanguis::client::control::actions::nullary_type::escape:
        case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
        case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
          return this->forward_event();
        }

        FCPPT_ASSERT_UNREACHABLE;
      });
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(sanguis::client::events::overlay const &_event)
{
  perk_chooser_gui_.draw(_event.context());

  this->context<sanguis::client::machine>().cursor_gfx().draw(_event.context());

  return this->discard_event();
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(sanguis::client::events::tick const &_event)
{
  perk_chooser_gui_.process(_event.delta());

  return this->forward_event();
}

boost::statechart::result
sanguis::client::states::perk_chooser::react(sanguis::client::events::input const &_event)
{
  perk_chooser_gui_.input(_event.get());

  return this->forward_event();
}
