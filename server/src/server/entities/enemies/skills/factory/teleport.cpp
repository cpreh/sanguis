#include <sanguis/duration_second.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/teleport.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/factory/teleport.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::skills::unique_ptr
sanguis::server::entities::enemies::skills::factory::teleport(
	sanguis::server::entities::enemies::skills::factory::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::skills::teleport
		>(
			_parameters.diff_clock(),
			sanguis::server::entities::enemies::skills::cooldown(
				sanguis::duration_second(
					10.f
				)
				/
				std::sqrt(
					_parameters.difficulty().get()
				)
			)
		);
}
