#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_boss.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/boss.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/make_boss.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::make_boss(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::parameters &&_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::boss
		>(
			std::move(
				_parameters
				.ai(
					sanguis::server::ai::create_boss(
						_random_generator,
						sanguis::server::ai::sight_range(
							1000.f
						)
					)
				)
			)
		);
}
