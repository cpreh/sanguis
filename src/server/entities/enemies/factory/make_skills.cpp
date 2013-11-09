#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/factory/make_skills.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/teleport.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <functional>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

// TODO: Put this in multiple functions!

typedef
std::function<
	sanguis::server::entities::enemies::skills::unique_ptr (
		sanguis::diff_clock const &,
		sanguis::server::entities::enemies::difficulty
	)
>
callback;

typedef
std::vector<
	callback
>
callback_vector;

callback_vector const callbacks{
	callback(
		[](
			sanguis::diff_clock const &_diff_clock,
			sanguis::server::entities::enemies::difficulty const _difficulty
		)
		{
			return
				fcppt::make_unique_ptr<
					sanguis::server::entities::enemies::skills::teleport
				>(
					_diff_clock,
					sanguis::server::entities::enemies::skills::cooldown(
						sanguis::duration_second(
							10.f
						)
						/
						std::sqrt(
							_difficulty.get()
						)
					)
				);
		}
	)
};

}

sanguis::server::entities::enemies::skills::container
sanguis::server::entities::enemies::factory::make_skills(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	auto distribution(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices(
				callbacks
			)
		)
	);

	// TODO: Choose multiple!
	return
		sanguis::server::entities::enemies::skills::container(
			fcppt::assign::make_container<
				sanguis::server::entities::enemies::skills::container
			>(
				callbacks[
					distribution(
						_random_generator
					)
				](
					_diff_clock,
					_difficulty
				)
			).move_container()
		);
}
