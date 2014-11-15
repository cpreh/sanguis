#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/enemy_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <fcppt/text.hpp>


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
/*
	fcppt::algorithm::repeat(
		4u,
		[]
		{
			_enemy.environment()->insert(
				fcppt::make_unique_ptr<
					sanguis::server::entities::enemies::enemy
				>(
					sanguis::server::entities::enemies::parameters{
						_enemy.enemy_type(),
						_enemy.environment()->load_context(),
						_enemy.armor_array(),
						_enemy.health()
						/
						sanguis::server::health{
							4.f
						},
						_enemy.ai_create_function(),
						// TODO!
						fcppt::make_unique_ptr<
							sanguis::server::weapons::melee
						>(
						),
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
			);
		}
	);*/
}

sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::skills::mother_spider::attribute() const
{
	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("mother spider")
		);
}
