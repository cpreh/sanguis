#include <sanguis/client/machine.hpp>
#include <sanguis/client/control/actions/nullary.hpp>
#include <sanguis/client/control/actions/nullary_type.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/input.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/message.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/net_error.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/overlay.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/render.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/tick.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/states/console.hpp>
#include <sanguis/client/states/ingame.hpp>
#include <sanguis/client/states/perk_chooser.hpp>
#include <sanguis/client/states/running.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::states::ingame::ingame(my_context _ctx) : my_base(std::move(_ctx)) {}

sanguis::client::states::ingame::~ingame() = default;

boost::statechart::result
sanguis::client::states::ingame::react(sanguis::client::events::action const &_event)
{
  return fcppt::optional::maybe(
      fcppt::variant::to_optional<sanguis::client::control::actions::nullary>(_event.value().get()),
      [this] { return this->forward_event(); },
      [this](sanguis::client::control::actions::nullary const &_nullary)
      {
        switch (_nullary.type())
        {
        case sanguis::client::control::actions::nullary_type::console:
          return this->transit<sanguis::client::states::console>();
        case sanguis::client::control::actions::nullary_type::perk_menu:
          return this->transit<sanguis::client::states::perk_chooser>();
        case sanguis::client::control::actions::nullary_type::escape:
          this->context<sanguis::client::machine>().quit();

          //return transit<states::ingame_menu>();
          return this->discard_event();
        case sanguis::client::control::actions::nullary_type::change_world:
        case sanguis::client::control::actions::nullary_type::drop_primary_weapon:
        case sanguis::client::control::actions::nullary_type::drop_secondary_weapon:
        case sanguis::client::control::actions::nullary_type::reload_primary_weapon:
        case sanguis::client::control::actions::nullary_type::reload_secondary_weapon:
          return this->forward_event();
        }

        FCPPT_ASSERT_UNREACHABLE;
      });
}
