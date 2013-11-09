#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/factory/make_modifiers.hpp>
#include <sanguis/server/entities/enemies/factory/make_skills.hpp>
#include <sanguis/server/entities/enemies/factory/make_special.hpp>
#include <sanguis/server/entities/enemies/modifiers/apply.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::make_special(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::parameters &&_parameters
)
{
	sanguis::diff_clock const &diff_clock(
		_parameters.diff_clock()
	);

	sanguis::server::entities::enemies::difficulty const difficulty(
		_parameters.difficulty()
	);

	sanguis::server::entities::enemies::attribute_container const modifier_result(
		sanguis::server::entities::enemies::modifiers::apply(
			_parameters,
			sanguis::server::entities::enemies::factory::make_modifiers(
				_random_generator,
				difficulty
			)
		)
	);

	_parameters.health(
		_parameters.health()
		*
		sanguis::server::health(
			5.f
		)
	);

	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::special
		>(
			std::move(
				_parameters
			),
			modifier_result,
			sanguis::server::entities::enemies::factory::make_skills(
				diff_clock,
				_random_generator,
				difficulty
			)
		);
}
