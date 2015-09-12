#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/is_unique.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/factory/make_modifiers.hpp>
#include <sanguis/server/entities/enemies/factory/make_skills.hpp>
#include <sanguis/server/entities/enemies/factory/make_special.hpp>
#include <sanguis/server/entities/enemies/modifiers/amount.hpp>
#include <sanguis/server/entities/enemies/modifiers/apply.hpp>
#include <sanguis/server/entities/enemies/skills/amount.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/max.hpp>
#include <sanguis/server/random/min.hpp>
#include <sanguis/server/random/split.hpp>
#include <sanguis/server/random/split_array.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_id_unique_ptr
sanguis::server::entities::enemies::factory::make_special(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::parameters &&_parameters,
	sanguis::server::entities::enemies::is_unique const _is_unique
)
{
	typedef
	sanguis::server::random::split_array<
		2
	>
	split_array;

	split_array const amounts(
		sanguis::server::random::split(
			_random_generator,
			sanguis::server::random::min(
				sanguis::server::random::amount(
					_is_unique.get()
					?
						3u
					:
						1u
				)
			),
			sanguis::server::random::max(
				sanguis::server::random::amount(
					_is_unique.get()
					?
						5u
					:
						2u
				)
			),
			split_array{{
				sanguis::server::entities::enemies::modifiers::amount(),
				sanguis::server::entities::enemies::skills::amount()
			}}
		)
	);

	sanguis::server::entities::enemies::attribute_container const modifier_result(
		sanguis::server::entities::enemies::modifiers::apply(
			_random_generator,
			_parameters,
			sanguis::server::entities::enemies::factory::make_modifiers(
				_random_generator,
				amounts[
					0
				]
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
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::with_id
		>(
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::special
			>(
				_random_generator,
				std::move(
					_parameters
				),
				modifier_result,
				sanguis::server::entities::enemies::factory::make_skills(
					_random_generator,
					amounts[
						1
					]
				),
				_is_unique
			)
		);
}
