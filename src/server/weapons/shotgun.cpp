#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/shotgun_parameters.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/make.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/normal.hpp>


sanguis::server::weapons::shotgun::shotgun(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::weapons::shotgun_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		_weapon_type,
		sanguis::server::weapons::attributes::optional_accuracy(
			_parameters.accuracy()
		),
		_parameters.range(),
		sanguis::server::weapons::attributes::optional_magazine_size(
			_parameters.magazine_size()
		),
		_parameters.base_cooldown(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time(
			_parameters.reload_time()
		)
	),
	random_generator_(
		_random_generator
	),
	spread_radius_(
		_parameters.spread_radius()
	),
	shells_(
		_parameters.shells()
	),
	damage_(
		_parameters.damage()
	)
{
}

sanguis::server::weapons::shotgun::~shotgun()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::shotgun::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::normal<
			sanguis::server::space_unit
		>
	> angle_distribution;

	fcppt::random::variate<
		sanguis::random_generator,
		angle_distribution
	> angle_rng(
		random_generator_,
		angle_distribution(
			angle_distribution::param_type::mean(
				_attack.angle().get()
			),
			angle_distribution::param_type::stddev(
				spread_radius_.value().get()
			)
		)
	);

	fcppt::algorithm::repeat(
		shells_.get(),
		[
			&angle_rng,
			&_attack,
			this
		]()
		{
			sanguis::server::angle const angle(
				angle_rng()
			);

			sanguis::server::environment::insert_no_result(
				_attack.environment(),
				fcppt::make_unique_ptr<
					sanguis::server::entities::projectiles::simple_bullet
				>(
					this->diff_clock(),
					_attack.environment().load_context(),
					_attack.team(),
					damage_.value(),
					sanguis::server::direction(
						angle.get()
					)
				),
				sanguis::server::entities::insert_parameters(
					_attack.spawn_point(),
					angle
				)
			);
		}
	);

	return
		sanguis::server::weapons::attack_result::success;
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::shotgun::attributes() const
{
	return
		sanguis::weapon_attribute_vector{
			sanguis::server::weapons::attributes::make_damage(
				damage_
			),
			sanguis::server::weapons::attributes::make(
				sanguis::weapon_attribute_type::spread_radius,
				spread_radius_
			)
		};
}
