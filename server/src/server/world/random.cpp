#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate.hpp>
#include <sanguis/server/world/object.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <sanguis/server/world/random.hpp>
#include <sanguis/server/world/random_generator_name.hpp>
#include <sanguis/server/world/random_seed.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>

sanguis::server::world::object_unique_ptr sanguis::server::world::random(
    sanguis::server::world::parameters const &_parameters,
    sanguis::creator::opening_count_array const _opening_count_array,
    sanguis::creator::spawn_boss const _spawn_boss,
    sanguis::world_id const _world_id,
    sanguis::server::world::difficulty const _difficulty)
{
  return sanguis::server::world::generate(
      _parameters,
      _world_id,
      sanguis::world_name(FCPPT_TEXT("World ") + fcppt::output_to_fcppt_string(_world_id)),
      _difficulty,
      sanguis::creator::top_parameters{
          fcppt::make_ref(_parameters.log_context()),
          sanguis::server::world::random_generator_name(_parameters.random_generator()),
          sanguis::server::world::random_seed(_parameters.random_generator()),
          _opening_count_array,
          _spawn_boss});
}
