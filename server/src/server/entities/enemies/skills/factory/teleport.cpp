#include <sanguis/duration_second.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/teleport.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/factory/teleport.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::skills::unique_ptr
sanguis::server::entities::enemies::skills::factory::teleport(
	sanguis::server::entities::enemies::skills::factory::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::enemies::skills::skill
		>(
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::skills::teleport
			>(
				fcppt::make_cref(
					_parameters.diff_clock()
				),
				sanguis::server::entities::enemies::skills::cooldown(
					sanguis::duration_second(
						10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					)
					/
					std::sqrt(
						_parameters.difficulty().get()
					)
				)
			)
		);
}
