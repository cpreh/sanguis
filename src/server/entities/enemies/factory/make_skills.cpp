#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/random/draw.hpp>
#include <sanguis/server/random/max.hpp>
#include <sanguis/server/random/min.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/factory/make_skills.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/factory/teleport.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

using
callback
=
sanguis::server::entities::enemies::skills::unique_ptr
(*)(
	sanguis::server::entities::enemies::skills::factory::parameters const &
);

typedef
std::vector<
	callback
>
callback_vector;

callback_vector const callbacks{
	&sanguis::server::entities::enemies::skills::factory::teleport
};

}

sanguis::server::entities::enemies::skills::container
sanguis::server::entities::enemies::factory::make_skills(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	return
		sanguis::server::random::draw<
			sanguis::server::entities::enemies::skills::container
		>(
			_random_generator,
			callbacks,
			sanguis::server::random::min(
				0u
			),
			sanguis::server::random::max(
				2u
			), // TODO: How many?
			[
				&_diff_clock,
				_difficulty
			](
				callback const &_callback
			)
			{
				return
					_callback(
						sanguis::server::entities::enemies::skills::factory::parameters(
							_diff_clock,
							_difficulty
						)
					);
			},
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
			},
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
		);
}
