#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/net_error.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/tick.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/states/console.hpp>
#include <sanguis/client/states/has_player.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/running.hpp>
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

sanguis::client::states::console::console(my_context _ctx)
    : my_base(std::move(_ctx)),
      pause_(sanguis::client::make_send_callback(
          fcppt::make_ref(this->context<sanguis::client::machine>())))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::states::console::~console() = default;

boost::statechart::result
sanguis::client::states::console::react(sanguis::client::events::action const &_event)
{
  return fcppt::optional::maybe(
      fcppt::variant::to_optional<sanguis::client::control::actions::nullary>(_event.value().get()),
      [this] { return this->discard_event(); },
      [this](sanguis::client::control::actions::nullary const &_nullary)
      {
        switch (_nullary.type())
        {
        case sanguis::client::control::actions::nullary_type::console:
          return this->transit<sanguis::client::states::ingame>();
        case sanguis::client::control::actions::nullary_type::change_world:
        case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
        case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
        case sanguis::client::control::actions::nullary_type::escape:
        case sanguis::client::control::actions::nullary_type::perk_menu:
        case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
        case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
          return this->discard_event();
        }

        FCPPT_ASSERT_UNREACHABLE;
      });
}

boost::statechart::result
sanguis::client::states::console::react(sanguis::client::events::overlay const &_event)
{
  this->context<sanguis::client::states::running>().console().draw(_event.context());

  return this->forward_event();
}

boost::statechart::result
sanguis::client::states::console::react(sanguis::client::events::input const &_event)
{
  this->context<sanguis::client::states::running>().console().input_event(_event.get());

  return this->forward_event();
}
