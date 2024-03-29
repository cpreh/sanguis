#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/ai/create_boss.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/boss.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/make_boss.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::with_id_unique_ptr
sanguis::server::entities::enemies::factory::make_boss(
    sanguis::random_generator_ref const _random_generator,
    // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
    sanguis::server::entities::enemies::parameters &&_parameters)
{
  return fcppt::unique_ptr_to_base<sanguis::server::entities::with_id>(
      fcppt::make_unique_ptr<sanguis::server::entities::enemies::boss>(
          std::move(_parameters.ai(sanguis::server::ai::create_boss(
              _random_generator,
              sanguis::server::ai::sight_range(
                  1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ))))));
}
