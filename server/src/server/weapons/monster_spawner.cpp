#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>
#include <sanguis/server/weapons/monster_spawner.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_enum.hpp>


sanguis::server::weapons::monster_spawner::monster_spawner(
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::weapons::weapon(
		_random_generator,
		sanguis::weapon_type(
			sanguis::primary_weapon_type::pistol
		),
		sanguis::server::weapons::attributes::optional_accuracy(),
		sanguis::server::weapons::range(
			1000.f
		),
		sanguis::server::weapons::attributes::optional_magazine_size(),
		sanguis::server::weapons::backswing_time(
			sanguis::duration_second(
				0.8f
			)
		),
		sanguis::server::weapons::cast_point(
			sanguis::duration_second(
				0.2f
			)
		),
		sanguis::server::weapons::optional_reload_time()
	)
{
}

sanguis::server::weapons::monster_spawner::~monster_spawner()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::monster_spawner::do_attack(
	sanguis::server::weapons::attack const &_attack
)
{
	return
		sanguis::server::weapons::insert_to_attack_result(
			_attack.environment().insert(
				sanguis::server::entities::enemies::create(
					this->random_generator(),
					fcppt::random::distribution::make_basic(
						fcppt::random::distribution::parameters::make_uniform_enum<
							sanguis::creator::enemy_type
						>()
					)(
						this->random_generator()
					),
					sanguis::creator::enemy_kind::normal,
					_attack.environment().difficulty(),
					_attack.environment().load_context(),
					sanguis::server::entities::spawn_owner(
						sanguis::server::entities::auto_weak_link()
					),
					sanguis::server::entities::enemies::special_chance(
						1.f
					)
				),
				sanguis::server::entities::insert_parameters(
					sanguis::server::center(
						_attack.target().get()
					),
					_attack.angle()
				)
			)
		);
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::monster_spawner::attributes() const
{
	return
		sanguis::weapon_attribute_vector();
}
