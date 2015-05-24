#include <sanguis/duration_second.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/scatter.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/factory/scatter.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::server::entities::enemies::skills::unique_ptr
sanguis::server::entities::enemies::skills::factory::scatter(
	sanguis::server::entities::enemies::skills::factory::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::enemies::skills::skill
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::server::entities::enemies::skills::scatter
			>(
				_parameters.diff_clock(),
				_parameters.random_generator(),
				sanguis::server::entities::enemies::skills::cooldown(
					sanguis::duration_second(
						5.f
					)
				)
			)
		);
}
