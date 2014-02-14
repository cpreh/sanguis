#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/special.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/reaper.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/regenerating.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/factory/scatter.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::reaper(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	sanguis::server::entities::enemies::parameters enemy_parameters(
		_parameters.diff_clock(),
		_parameters.random_generator(),
		_parameters.enemy_type(),
		_parameters.load_context(),
		sanguis::server::damage::no_armor(),
		sanguis::server::health(
			100.f
			*
			std::sqrt(
				_parameters.difficulty().get()
			)
		),
		sanguis::server::entities::movement_speed(
			150.f
		),
		sanguis::server::ai::create_simple(
			sanguis::server::ai::sight_range(
				1000.f
			)
		),
		fcppt::make_unique_ptr<
			sanguis::server::weapons::melee
		>(
			_parameters.diff_clock(),
			_parameters.random_generator(),
			sanguis::server::weapons::range(
				75.f
			),
			sanguis::server::weapons::base_cooldown(
				sanguis::duration_second(
					2.f
				)
			),
			sanguis::server::weapons::damage(
				5.f
				*
				std::sqrt(
					_parameters.difficulty().get()
				)
			),
			sanguis::server::damage::list{
				sanguis::server::damage::normal =
					sanguis::server::damage::full
			}
		),
		sanguis::server::pickup_probability(
			0.f
		),
		sanguis::server::exp(
			0.f
		),
		_parameters.difficulty(),
		_parameters.spawn_owner(),
		sanguis::server::auras::container(
			// TODO
		)
	);

	sanguis::server::entities::enemies::modifiers::parameters const modifiers_parameters(
		_parameters.random_generator()
	);

	sanguis::server::entities::enemies::attribute_container const attributes{
		sanguis::server::entities::enemies::modifiers::regenerating(
			enemy_parameters,
			modifiers_parameters
		)
	};

	sanguis::server::entities::enemies::skills::factory::parameters const skills_parameters(
		_parameters.diff_clock(),
		_parameters.random_generator(),
		_parameters.difficulty()
	);

	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::special
		>(
			std::move(
				enemy_parameters
			),
			attributes,
			fcppt::assign::make_container<
				sanguis::server::entities::enemies::skills::container
			>(
				sanguis::server::entities::enemies::skills::factory::scatter(
					skills_parameters
				)
			).move_container()
		);
}
