#include <sanguis/duration.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/patrol.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/random/grid_distance.hpp>
#include <sanguis/server/random/grid_pos_around.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/optional/maybe.hpp>

sanguis::server::ai::behavior::patrol::patrol(
    sanguis::server::ai::context_ref const _context,
    sanguis::random_generator_ref const _random_generator)
    : sanguis::server::ai::behavior::base(_context),
      random_generator_(_random_generator),
      start_pos_{sanguis::server::world::center_to_grid_pos(_context->me().center())}
{
}

sanguis::server::ai::behavior::patrol::~patrol() = default;

bool sanguis::server::ai::behavior::patrol::start()
{
  return fcppt::optional::maybe(
      sanguis::server::random::grid_pos_around(
          random_generator_.get(),
          this->context().grid().size(),
          start_pos_,
          sanguis::server::random::grid_distance{
              5U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          }),
      fcppt::const_(false),
      [this](sanguis::creator::pos const &_pos)
      { return sanguis::server::ai::make_path(this->context(), _pos); });
}

sanguis::server::ai::status sanguis::server::ai::behavior::patrol::update(sanguis::duration)
{
  return sanguis::server::ai::go_to_grid_pos(
      this->context(),
      fcppt::literal<sanguis::server::ai::speed_factor>(
          0.3F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));
}
