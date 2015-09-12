#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/normal.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/assert/optional_error.hpp>


sanguis::server::entities::enemies::skills::mother_spider::mother_spider()
{
}

sanguis::server::entities::enemies::skills::mother_spider::~mother_spider()
{
}

void
sanguis::server::entities::enemies::skills::mother_spider::on_die(
	sanguis::server::entities::enemies::enemy const &_enemy
)
{
	sanguis::server::weapons::weapon const &primary_weapon(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			_enemy.primary_weapon()
		)
	);

	sanguis::server::environment::object &environment(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			_enemy.environment()
		)
	);

	// TODO: Make copies of enemies smaller
	fcppt::algorithm::repeat(
		1u,
		[
			&_enemy,
			&primary_weapon,
			&environment
		]
		{
			sanguis::server::environment::insert_no_result(
				environment,
				fcppt::unique_ptr_to_base<
					sanguis::server::entities::with_id
				>(
					fcppt::make_unique_ptr<
						sanguis::server::entities::enemies::normal
					>(
						sanguis::server::entities::enemies::parameters{
							_enemy.enemy_type(),
							environment.load_context(),
							_enemy.armor(),
							_enemy.mass(),
							// TODO: This parameter should probably be of type max_health
							sanguis::server::health{
								_enemy.max_health().get()
							}
							/
							sanguis::server::health{
								4.f
							},
							_enemy.max_movement_speed(),
							_enemy.create_ai(),
							primary_weapon.clone(),
							sanguis::server::pickup_probability{
								0.f
							},
							_enemy.exp()
							/
							sanguis::server::exp{
								4.f
							},
							_enemy.difficulty(),
							sanguis::server::entities::spawn_owner(
								sanguis::server::entities::auto_weak_link{}
							),
							sanguis::server::auras::container{}
						}
					)
				),
				sanguis::server::entities::insert_parameters_center(
					_enemy.center()
				)
			);
		}
	);
}

sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::skills::mother_spider::attribute() const
{
	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("mother spider")
		);
}
