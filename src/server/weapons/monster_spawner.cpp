#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/monster_spawner.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>


sanguis::server::weapons::monster_spawner::monster_spawner(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		sanguis::weapon_type(
			sanguis::primary_weapon_type::pistol
		),
		sanguis::server::weapons::accuracy(
			1.f
		),
		sanguis::server::weapons::range(
			1000.f
		),
		sanguis::server::weapons::optional_magazine_size(
			sanguis::server::weapons::magazine_size(
				1u
			)
		),
		sanguis::server::weapons::base_cooldown(
			sanguis::duration_second(
				1.f
			)
		),
		sanguis::server::weapons::cast_point(
			sanguis::duration_second(
				0.2f
			)
		),
		sanguis::server::weapons::optional_reload_time(
			sanguis::server::weapons::reload_time(
				sanguis::duration_second(
					0.5f
				)
			)
		)
	)
{
}

sanguis::server::weapons::monster_spawner::~monster_spawner()
{
}

bool
sanguis::server::weapons::monster_spawner::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	return
		_attack.environment().insert(
			sanguis::server::entities::enemies::create(
				this->diff_clock(),
				this->random_generator(),
				sanguis::creator::enemy_type::ghost,
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
		).has_value();
}

sanguis::string_vector
sanguis::server::weapons::monster_spawner::attributes() const
{
	return
		sanguis::string_vector();
}
