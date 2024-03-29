#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/go_close_to_target.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/follow_owner.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::ai::behavior::follow_owner::follow_owner(
    sanguis::server::ai::context_ref const _context,
    sanguis::server::entities::spawn_owner _spawn_owner)
    : sanguis::server::ai::behavior::base(_context), spawn_owner_{std::move(_spawn_owner)}
{
}

sanguis::server::ai::behavior::follow_owner::~follow_owner() = default;

bool sanguis::server::ai::behavior::follow_owner::start()
{
  return spawn_owner_.get().get().has_value();
}

sanguis::server::ai::status sanguis::server::ai::behavior::follow_owner::update(sanguis::duration)
{
  return fcppt::optional::maybe(
      spawn_owner_.get().get(),
      [] { return sanguis::server::ai::status::failure; },
      [this](fcppt::reference<sanguis::server::entities::with_links> const _spawn_owner)
      {
        return sanguis::server::ai::go_close_to_target(
                   this->context(),
                   sanguis::server::ai::target{_spawn_owner.get().center()},
                   fcppt::literal<sanguis::server::ai::speed_factor>(1))
                   ? sanguis::server::ai::status::running
                   : sanguis::server::ai::status::failure;
      });
}
