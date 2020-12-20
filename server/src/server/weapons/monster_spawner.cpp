#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>
#include <sanguis/server/weapons/monster_spawner.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_enum.hpp>


sanguis::server::weapons::monster_spawner::monster_spawner(
	sanguis::server::weapons::common_parameters const &_common_parameters
)
:
	sanguis::server::weapons::weapon(
		sanguis::server::weapons::parameters{
			_common_parameters,
			sanguis::weapon_type(
				sanguis::primary_weapon_type::pistol
			),
			sanguis::server::weapons::attributes::optional_accuracy(),
			sanguis::server::weapons::range(
				1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			),
			sanguis::server::weapons::attributes::optional_magazine_size(),
			sanguis::server::weapons::backswing_time(
				sanguis::duration_second(
					0.8F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			),
			sanguis::server::weapons::cast_point(
				sanguis::duration_second(
					0.2F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			),
			sanguis::server::weapons::optional_reload_time()
		}
	),
	common_parameters_{
		_common_parameters
	}
{
}

sanguis::server::weapons::monster_spawner::~monster_spawner()
= default;

sanguis::server::weapons::monster_spawner::monster_spawner(
	sanguis::server::weapons::parameters const &_parameters
)
:
	sanguis::server::weapons::weapon{
		_parameters
	},
	common_parameters_{
		_parameters.common_parameters()
	}
{
}

sanguis::server::weapons::unique_ptr
sanguis::server::weapons::monster_spawner::clone() const
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::weapons::weapon
		>(
			fcppt::make_unique_ptr<
				sanguis::server::weapons::monster_spawner
			>(
				this->parameters()
			)
		);
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
					fcppt::make_ref(
						this->random_generator()
					),
					common_parameters_,
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
						1.F
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
