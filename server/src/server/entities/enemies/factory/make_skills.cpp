#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/create_function.hpp>
#include <sanguis/server/random/draw.hpp>
#include <sanguis/server/random/equal_function.hpp>
#include <sanguis/server/random/less_function.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/factory/make_skills.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/callback.hpp>
#include <sanguis/server/entities/enemies/skills/factory/create_callbacks.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::skills::container
sanguis::server::entities::enemies::factory::make_skills(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::random::amount const _amount,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	return
		sanguis::server::random::draw<
			sanguis::server::entities::enemies::skills::container
		>(
			_random_generator,
			sanguis::server::entities::enemies::skills::factory::create_callbacks(),
			_amount,
			sanguis::server::random::create_function<
				sanguis::server::entities::enemies::skills::unique_ptr,
				sanguis::server::entities::enemies::skills::factory::callback
			>(
				[
					&_diff_clock,
					&_random_generator,
					_difficulty
				](
					sanguis::server::entities::enemies::skills::factory::callback const &_callback
				)
				{
					return
						_callback(
							sanguis::server::entities::enemies::skills::factory::parameters(
								_diff_clock,
								_random_generator,
								_difficulty
							)
						);
				}
			),
			sanguis::server::random::less_function<
				sanguis::server::entities::enemies::skills::unique_ptr
			>(
				[](
					sanguis::server::entities::enemies::skills::unique_ptr const &_skill1,
					sanguis::server::entities::enemies::skills::unique_ptr const &_skill2
				)
				{
					return
						typeid(
							*_skill1
						).before(
							typeid(
								*_skill2
							)
						);
				}
			),
			sanguis::server::random::equal_function<
				sanguis::server::entities::enemies::skills::unique_ptr
			>(
				[](
					sanguis::server::entities::enemies::skills::unique_ptr const &_skill1,
					sanguis::server::entities::enemies::skills::unique_ptr const &_skill2
				)
				{
					return
						typeid(
							*_skill1
						)
						==
						typeid(
							*_skill2
						);
				}
			)
		);
}
